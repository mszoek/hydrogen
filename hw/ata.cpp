// ATA IDE driver
// Zoe Knox 2019

#include <hw/port_io.h>
#include <hw/ata.h>
#include <drivers/screen.h>
#include <kstring.h>

extern UInt32 tickCounter;

struct ideChannel ideChannels[2];
struct ideDevice ideDevices[4];
UInt8 ideBuffer[2048];

static UInt8 ideIRQ = 0;
static UInt8 atapiPacket[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

UInt8 ideRead(UInt8 channel, UInt8 reg)
{
    UInt8 result;
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN | 0x80);

    if(reg < 0x08)
        result = portByteIn(ideChannels[channel].baseIO + reg);
    else if(reg < 0x0C)
        result = portByteIn(ideChannels[channel].baseIO + reg - 0x06);
    else if(reg < 0x0E)
        result = portByteIn(ideChannels[channel].baseCtrl + reg - 0x0A);
    else if(reg < 0x16)
        result = portByteIn(ideChannels[channel].baseBM + reg - 0x0E);
    
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN);
    
    return result;
}

void ideWrite(UInt8 channel, UInt8 reg, UInt8 data)
{
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN | 0x80);
    if(reg < 0x08)
        portByteOut(data, ideChannels[channel].baseIO + reg);
    else if(reg < 0x0C)
        portByteOut(data, ideChannels[channel].baseIO + reg - 0x06);
    else if(reg < 0x0E)
        portByteOut(data, ideChannels[channel].baseCtrl + reg - 0x0A);
    else if(reg < 0x16)
        portByteOut(data, ideChannels[channel].baseBM + reg - 0x0E);

    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN);
}

void insl(UInt32 port, void *buffer, int count)
{
    asm volatile("cld; rep; insl;"
        : "=D"(buffer), "=c"(count)
        : "d"(port), "0"(buffer), "1"(count)
        : "memory", "cc");
}

void ideReadBuffer(UInt8 channel, UInt8 reg, UInt32 buffer, UInt32 count)
{
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN | 0x80);
    
    asm("pushw %es; movw %ds, %ax; movw %ax, %es");

    if(reg < 0x08)
        insl(ideChannels[channel].baseIO + reg, (void*)buffer, count);
    else if(reg < 0x0C)
        insl(ideChannels[channel].baseIO + reg - 0x06, (void *)buffer, count);
    else if(reg < 0x0E)
        insl(ideChannels[channel].baseCtrl + reg - 0x0A, (void *)buffer, count);
    else if(reg < 0x16)
        insl(ideChannels[channel].baseBM + reg - 0x0E, (void *)buffer, count);

    asm("popw %es;");
   
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN);
}

UInt8 idePoll(UInt8 channel)
{
   // wait 400ns for BSY to be set
   // Reading Alternate Status Port wastes 100ns
   ideRead(channel, ATA_REG_ALTSTATUS);
   ideRead(channel, ATA_REG_ALTSTATUS);
   ideRead(channel, ATA_REG_ALTSTATUS);
   ideRead(channel, ATA_REG_ALTSTATUS);

   // wait for BSY to clear
   while(ideRead(channel, ATA_REG_STATUS) & ATA_SR_BSY);

    UInt8 state = ideRead(channel, ATA_REG_STATUS); // read Status Register

    if (state & ATA_SR_ERR) return 2; // Error.
    if (state & ATA_SR_DF ) return 1; // Device Fault.
    // if BSY = 0 and DF = 0 and ERR = 0, we should check DRQ
    if (!(state & ATA_SR_DRQ)) return 3; // DRQ should be set

    return 0; // everything is awesome
}

// translate error codes from idePoll and optionally print error msg
UInt8 ideError(UInt32 drive, UInt8 error, bool printError)
{
    char errmsg[40];
    UInt8 status;

    switch(error)
    {
        case 1:
            strcpy(errmsg, "Device fault");
            error = 19;
            break;
        case 2:
            status = ideRead(ideDevices[drive].channel, ATA_REG_ERROR);
            if(status & ATA_ERR_AMNF)
            {
                strcpy(errmsg, "Address mark not found");
                error = 7;
            }
            else if(status & ATA_ERR_TK0NF || status & ATA_ERR_MCR || status & ATA_ERR_MC)
            {
                strcpy(errmsg, "Media error");
                error = 3;
            }
            else if(status & ATA_ERR_ABRT)
            {
                strcpy(errmsg, "Command aborted");
                error = 20;
            }
            else if(status & ATA_ERR_IDNF)
            {
                strcpy(errmsg, "ID mark not found");
                error = 21;
            }
            else if(status & ATA_ERR_UNC)
            {
                strcpy(errmsg, "Uncorrectable data error");
                error = 22;
            }
            else if(status & ATA_ERR_BBK)
            {
                strcpy(errmsg, "Bad blocks");
                error = 13;
            }
            break;
        case 3:
            strcpy(errmsg, "Empty read");
            error = 23;
            break;
        case 4:
            strcpy(errmsg, "Write protected");
            error = 8;
            break;
        default:
            strcpy(errmsg, "Unknown error");
            error = 19;
    }

    if(printError)
    {
        kprintf("ATA: Ch %d Port %d: %s\n", ideDevices[drive].channel,
            ideDevices[drive].drive, errmsg);
    }

   return error;
}

void ideInit(UInt32 BAR0, UInt32 BAR1, UInt32 BAR2, UInt32 BAR3, UInt32 BAR4)
{
    int i, j, k, count = 0;
    UInt32 ticks;

    /* set up the i/o ports for IDE controller */
    ideChannels[ATA_PRIMARY].baseIO  = (BAR0 &= 0xFFFFFFFC) + 0x1F0*(!BAR0);
    ideChannels[ATA_PRIMARY].baseCtrl  = (BAR1 &= 0xFFFFFFFC) + 0x3F4*(!BAR1);
    ideChannels[ATA_SECONDARY].baseIO  = (BAR2 &= 0xFFFFFFFC) + 0x170*(!BAR2);
    ideChannels[ATA_SECONDARY].baseCtrl  = (BAR3 &= 0xFFFFFFFC) + 0x374*(!BAR3);
    ideChannels[ATA_PRIMARY].baseBM = (BAR4 &= 0xFFFFFFFC) + 0; // Bus Master IDE
    ideChannels[ATA_SECONDARY].baseBM = (BAR4 &= 0xFFFFFFFC) + 8; // Bus Master IDE

    /* temp disable interrupts */
    ideWrite(ATA_PRIMARY, ATA_REG_CONTROL, 2);
    ideWrite(ATA_SECONDARY, ATA_REG_CONTROL, 2);

    /* now detect devices! */
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            UInt8 error = 0;
            UInt8 type = IDE_ATA;
            UInt8 status;

            kprintf("ATA detection i=%d j=%d\n", i, j);
            ideDevices[count].reserved = 0; // Assuming that no drive here.

            ticks = tickCounter + 1;
            ideWrite(i, ATA_REG_HDDEVSEL, 0xA0 | (j<<4)); // Select Drive.
            while(tickCounter < ticks);  // wait 1ms

            ticks = tickCounter + 1;
            ideWrite(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
            while(tickCounter < ticks);  // wait 1ms

            if(ideRead(i, ATA_REG_STATUS) == 0) // 0 = no device
            {
                kprint("no device\n");
                continue;
            }

            while(1)
            {
                status = ideRead(i, ATA_REG_STATUS);
                kprintf("status = %x\n", status);
                if(!(status & ATA_SR_BSY))
                {
                    if(status & ATA_SR_DRQ)
                        break;
                    else
                    {
                        error = 1;
                        break;
                    }
                }
            }

            // check for ATAPI devices now

            if(error)
            {
                UInt8 cl = ideRead(i, ATA_REG_LBA1);
                UInt8 ch = ideRead(i, ATA_REG_LBA2);

                if(cl == 0x14 && ch ==0xEB)
                    type = IDE_ATAPI;
                else if(cl == 0x69 && ch ==0x96)
                    type = IDE_ATAPI;
                else
                    continue; // no idea what this is!

                ticks = tickCounter + 1;
                ideWrite(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
                while(tickCounter < ticks); // wait 1ms
            }

            /* OK! read the ID space of the device! */
            ideReadBuffer(i, ATA_REG_DATA, (UInt32)ideBuffer, 128);

            ideDevices[count].reserved = 1;
            ideDevices[count].type = type;
            ideDevices[count].channel = i;
            ideDevices[count].drive = j;
            ideDevices[count].signature = ((UInt16 *)(ideBuffer + ATA_IDENT_DEVICETYPE))[0];
            ideDevices[count].caps = ((UInt16 *)(ideBuffer + ATA_IDENT_CAPABILITIES))[0];
            ideDevices[count].cmdSets = ((UInt32 *)(ideBuffer + ATA_IDENT_COMMANDSETS))[0];

            if(ideDevices[count].cmdSets & (1<<26))
            {
                // Device uses 48-Bit addressing. Ignore the last 2 words for 32 bit OS
                ideDevices[count].size = ((UInt32 *)(ideBuffer + ATA_IDENT_MAX_LBA_EXT))[0];
            } else {
                // Device uses CHS or 28-bit addressing
                ideDevices[count].size = ((UInt32 *)(ideBuffer + ATA_IDENT_MAX_LBA))[0];
            }

            /* save the device model string */
            for(k = ATA_IDENT_MODEL; k < (ATA_IDENT_MODEL+40); k+=2)
            {
                ideDevices[count].model[k - ATA_IDENT_MODEL] = ideBuffer[k+1];
                ideDevices[count].model[(k+1) - ATA_IDENT_MODEL] = ideBuffer[k];
            }
            ideDevices[count].model[40] = 0;

            count++;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(ideDevices[i].reserved == 1)
        {
            kprintf("[Ch %d Port %d] %s drive %dGB (%s)\n",
                ideDevices[i].channel, ideDevices[i].drive,
                ideDevices[i].type == IDE_ATA ? "ATA" : "ATAPI",
                ideDevices[i].size/1024/1024/2,
                ideDevices[i].model);
        }
    }
}
