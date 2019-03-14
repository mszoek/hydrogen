// ATA IDE driver
// Zoe Knox 2019

#include <hw/port_io.h>
#include <hw/ata.h>

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

UInt8 ideWrite(UInt8 channel, UInt8 reg, UInt8 data)
{
    if(reg > 0x07 && reg < 0x0C)
        ideWrite(channel, ATA_REG_CONTROL, ideChannels[channel].nIEN) | 0x80;
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

void ideReadBuffer(UInt8 channel, UInt8 reg, UInt32 buffer, UInt32 count) {
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