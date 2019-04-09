 /*
 * H2 AHCI ATA/ATAPI Driver
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#include <hw/port_io.h>
#include <hw/ata.h>
#include <hw/screen.h>
#include <kstring.h>
#include <kstdio.h>
#include <kernel.h>

static UInt8 atapiPacket[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static char *trimSpaces(UInt8 *s, int len)
{
    --len;
    while(len > 0 && (s[len] == 0 || s[len] == 32))
        s[len--] = 0;
    return (char *)s;
}

AHCIController::AHCIController(hbaMem *p)
{
    if(verbose)
        kprintf("hw/AHCIController: 0x%x\n", this);
    g_controllers[CTRL_AHCI] = (UInt64)this;
    abar = p;

    // reserve 75 blocks for our data structures
    AHCI_BASE = vmm->remap((UInt64)vmm->malloc(75*PMM_BLOCK_SIZE), 75*PMM_BLOCK_SIZE);

    nrCmdSlots = ((abar->cap >> 8) & 0x1F) + 1;
    probeSATAPorts();
}

AHCIController::~AHCIController()
{
    g_controllers[CTRL_AHCI] = 0;
    void *p = (void *)AHCI_BASE;
    vmm->free(p);
}


int AHCIController::checkDriveType(hbaPort *port)
{
    UInt32 tssts = port->ssts;

    UInt8 ipm = (tssts >> 8) & 0x0F;
    UInt8 det = tssts & 0x0F;

    if(det != HBA_PORT_DET_PRESENT || ipm != HBA_PORT_IPM_ACTIVE)
        return AHCI_DEV_NULL;

    switch(port->sig)
    {
        case SATA_SIG_ATAPI: return AHCI_DEV_SATAPI;
        case SATA_SIG_SEMB: return AHCI_DEV_SEMB;
        case SATA_SIG_PM: return AHCI_DEV_PM;
        default: return AHCI_DEV_SATA;
    }
}

hbaPort *AHCIController::getPort(int i)
{
    return (hbaPort *)(&abar->ports[i]);
}

void AHCIController::probeSATAPorts()
{
    nrPorts = 0;
    UInt32 pi = abar->pi;
    int i = 0;
    while(i < 32)
    {
        hbaPort *port = &abar->ports[i];
        if(pi & 1)
        {
            ++nrPorts;
            int dt = checkDriveType(port);
            if(dt != AHCI_DEV_NULL)
            {
                rebasePort(port, i);
                kprintf("AHCI Port %d: %s drive\n", i,
                    dt == AHCI_DEV_SATA ? "SATA" :
                    dt == AHCI_DEV_SATAPI ? "SATAPI" :
                    dt == AHCI_DEV_SEMB ? "SEMB" : "PM");
                if(dt == AHCI_DEV_SATA)
                    identifyPort(port);
            }
        }

        pi >>= 1;
        ++i;
    }
}

void AHCIController::rebasePort(hbaPort *port, int portNumber)
{
    stopCommand(port);

    port->clbLo = AHCI_BASE + (portNumber << 10);
    port->clbHi = 0;
    memset((char *)port->clbLo, 0, 1024);

    port->fbLo = AHCI_BASE + (32 << 10) + (portNumber << 8);
    port->fbHi = 0;
    memset((char *)port->fbLo, 0, 256);

    hbaCmdHeader *cmdheader = (hbaCmdHeader *)(port->clbLo);
    for(int i = 0; i < 32; ++i)
    {
        cmdheader[i].prdtLen = 8; // 8 PRDT per command table
        cmdheader[i].ctbaLo = AHCI_BASE + (40 << 10) + (portNumber << 13) + (i << 8);
        cmdheader[i].ctbaHi = 0;
        memset((char *)cmdheader[i].ctbaLo, 0, 256);
    }

    startCommand(port);
}

void AHCIController::stopCommand(hbaPort *port)
{
    // clear ST bit and wait for FR and CR bits to clear
    port->cmd &= ~PORT_CMD_ST;
    port->cmd &= ~PORT_CMD_FRE;

    while(port->cmd & (PORT_CMD_FR | PORT_CMD_CR));
}

void AHCIController::startCommand(hbaPort *port)
{
    // wait for CR to clear
    while(port->cmd & PORT_CMD_CR);

    // set FRE and ST
    port->cmd |= PORT_CMD_FRE;
    port->cmd |= PORT_CMD_ST;
}

int AHCIController::findCmdSlot(hbaPort *port)
{
    // the slot is free if the corresponding bit in SACT and CI is not set
    UInt32 slots = (port->sact | port->ci);
    for(int i = 0; i < nrCmdSlots; ++i)
    {
        if(!(slots & 1)) return i;
        slots >>= 1; // shift them bits!
    }
    return -1;
}

void AHCIController::swapBytes(UInt8 *buf, UInt32 len)
{
    for(UInt32 i = 0; i < len; i += 2)
    {
        // we don't have ntohs() yet
        UInt16 *x = (UInt16 *)(buf + i);
        UInt8 a = (*x & 0xFF00) >> 8;
        *(UInt16 *)(buf + i) = (*x << 8) | a;
    }
}

void AHCIController::identifyPort(hbaPort *port)
{
    port->is = 0xFFFFFFFF;
    int spin = 0;
    UInt16 buf[512];

    int slot = findCmdSlot(port);
    if(slot < 0) return;

    hbaCmdHeader *hdr = (hbaCmdHeader *)(port->clbLo + slot);
    hdr->cfl = sizeof(eFISTypeRegH2D) / sizeof(UInt32);
    hdr->w = 0;
    hdr->prdtLen = 1;

    hbaCmdTable *tbl = (hbaCmdTable *)(hdr->ctbaLo);
    memset((char *)tbl, 0, sizeof(hbaCmdTable));

    tbl->prdtEntry[0].dbaLo = ((UInt64)buf) & 0xFFFFFFFF;
    tbl->prdtEntry[0].dbaHi = ((UInt64)buf) >> 32;
    tbl->prdtEntry[0].dbc = 512;
    tbl->prdtEntry[0].i = 1;

    SataFISRegH2D *fis = (SataFISRegH2D *)(&tbl->cFIS);
    fis->fisType = eFISTypeRegH2D;
    fis->command = ATA_CMD_IDENTIFY;
    fis->device = 0;
    fis->cc = 1;

    while((port->tfd & (ATA_SR_BSY | ATA_SR_DRQ)) && spin < 1000000)
        ++spin;
    if(spin == 1000000)
    {
        kprintf("AHCI: timeout; port not responding\n");
        return;
    }
    port->ci = 1;

    while(port->ci & 1);

    ATAIdentifyData *id = (ATAIdentifyData *)buf;
    swapBytes(id->ModelNumber, 40);
    id->ModelNumber[39] = 0;
    swapBytes(id->SerialNumber, 20);
    id->SerialNumber[19] = 0;

    kprintf("%s %s %dC %dH %dS\n", trimSpaces(id->ModelNumber, 40), trimSpaces(id->SerialNumber, 20),
        id->NumCylinders, id->NumHeads, id->NumSectorsPerTrack);
}

/* Read sectors into 'buf' which must be large enough for the data being read! */
bool AHCIController::read(hbaPort *port, UInt16 *buf, UInt32 lba, UInt16 sectors)
{
    port->is = 0xFFFFFFFF; // clear pending interrupts
    int spin = 0;

    int slot = findCmdSlot(port);
    if(slot < 0) return false;

    hbaCmdHeader *hdr = (hbaCmdHeader *)port->clbLo + slot;
    hdr->cfl = sizeof(SataFISRegH2D) / sizeof(UInt32);
    hdr->w = 0; // this is a read
    hdr->prdtLen = ((sectors - 1) >> 4) + 1; // count of PRDT entries
 
    hbaCmdTable *tbl = (hbaCmdTable *)hdr->ctbaLo;
    memset((char *)tbl, 0, sizeof(hbaCmdTable) + hdr->prdtLen * sizeof(hbaPRDTEntry));

    // load 8K (16 sectors) per PRDT
    int i;
    for(i = 0; i < hdr->prdtLen - 1; ++i)
    {
        tbl->prdtEntry[i].dbaLo = (UInt32)((UInt64)buf & 0xFFFFFFFF);
        tbl->prdtEntry[i].dbaHi = (UInt32)((UInt64)buf >> 32);
        tbl->prdtEntry[i].dbc = 8191; // always 1 less than actual value (8192 = 8K)
        tbl->prdtEntry[i].i = 1; // interrupt when ready
        buf += 4096; // 4K words = 8K bytes
        sectors -= 16;
    }
    tbl->prdtEntry[i].dbaLo = (UInt32)((UInt64)buf & 0xFFFFFFFF);
    tbl->prdtEntry[i].dbaHi = (UInt32)((UInt64)buf >> 32);
    tbl->prdtEntry[i].dbc = (sectors << 9) - 1; // 512 bytes per sector
    tbl->prdtEntry[i].i = 1;

    SataFISRegH2D *fis = (SataFISRegH2D *)(&tbl->cFIS);
    fis->fisType = eFISTypeRegH2D;
    fis->cc = 1; // command
    fis->command = ATA_CMD_READ_PIO;
    fis->lba0 = (UInt8)lba;
    fis->lba1 = (UInt8)(lba >> 8);
    fis->lba2 = (UInt8)(lba >> 16);
    fis->lba3 = (UInt8)(lba >> 24);
    fis->device = 1 << 6; // LBA mode
    fis->countLo = sectors & 0xFF;
    fis->countHi = (sectors >> 8) & 0xFF;

    // wait if port is busy
    while((port->tfd & (ATA_SR_BSY | ATA_SR_DRQ)) && spin < 1000000)
        ++spin;
    if(spin == 1000000)
    {
        kprintf("AHCI: timeout; port not responding\n");
        return false;
    }
    // send the command
    port->ci = 1;

    // wait for it to be done
    while(port->ci & (1 << slot))
    {
        if(port->is & (1<<30)) // check Task File Error Status (TFES)
            return false;
    }

    if(port->is & (1<<30))
        return false;
    return true;
}