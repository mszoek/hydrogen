// ATA IDE driver
// Zoe Knox 2019

#include <hw/port_io.h>
#include <hw/ata.h>
#include <hw/screen.h>
#include <kstring.h>

extern UInt32 tickCounter;
static UInt8 atapiPacket[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


static int checkDriveType(hbaPort *port)
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

void probeSATAPort(hbaMem *abar)
{
    UInt32 pi = abar->pi;
    int i = 0;
    while(i < 32)
    {
        if(pi & 1)
        {
            int dt = checkDriveType(&abar->ports[i]);
             kprintf("AHCI Port %d: %s drive\n", i,
                dt == AHCI_DEV_SATA ? "SATA" :
                dt == AHCI_DEV_SATAPI ? "SATAPI" :
                dt == AHCI_DEV_SEMB ? "SEMB" :
                dt == AHCI_DEV_PM ? "PM" : "No");
        }

        pi >>= 1;
        ++i;
    }
}

void rebasePort(hbaPort *port, int portNumber)
{
        
}