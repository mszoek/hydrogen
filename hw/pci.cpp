// H2OS PCI Bus driver
// Zoe Knox 2019

#include <hw/types.h>
#include <hw/port_io.h>
#include <hw/pci.h>
#include <drivers/screen.h>

char *pciClassCodes[] =
{
    "Unclassified", "Mass Storage Controller", "Network Controller", "Display Controller", "Multimedia Controller",
    "Memory Controller", "Bridge", "Simple Comm Controller", "Base System Peripheral", "Input Device Controller", "Docking Station",
    "Processor", "Serial Bus Controller", "Wireless Controller", "Intelligent Controller", "Satellite Comm Controller",
    "Encryption Controller", "Signal Processing Controller", "Processing Accelerator", "Non-essential Instrumentation"
};

UInt16 pciReadCfgWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset)
{
    UInt32 address;
    UInt16 result = 0;

    /*
    31     30-24    23-16 	 15-11  10-8     7-0
    Enable Reserved  Bus #  Device  Func  Reg Offset 
    */

    address = ((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xfc) | 0x80000000);

    portDWordOut(PCI_CFG_ADDR, address);

    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    result = (UInt16)((portDWordIn(PCI_CFG_DATA) >> ((offset & 2) * 8)) & 0xffff);
    return result;
}

void pciGetDevice(UInt32 bus, UInt32 slot)
{
    UInt32 function;
    UInt16 vendor, device, classcode, headertype;

    vendor = pciReadCfgWord(bus, slot, 0, 0);
    if(vendor == 0xFFFF) return;

    for(function = 0; function < 8; function++)
    {
        vendor = pciReadCfgWord(bus, slot, function, 0);
        if(vendor == 0xFFFF) continue;

        device = pciReadCfgWord(bus, slot, function, 2);
        classcode = pciReadCfgWord(bus, slot, function, 0x0a);
        headertype = pciReadCfgWord(bus, slot, function, 0x0e);

        kprintf("%d/%d.%d %x:%x class %x type %x %s\n", bus, slot, function,
            vendor, device, classcode & 0x7fff, headertype & 0x7f,
            pciClassCodes[((classcode & 0xFF00) >> 8) % 13]);
        if(headertype & 0x80 == 0) break;
    }
 }
 
void pciEnumBuses(void)
{
    UInt32 bus, slot;

    kprint("Enumerating PCI buses\n");
    for(bus = 0; bus < 256; bus++)
    {
        for(slot = 0; slot < 32; slot++)
        {
            pciGetDevice(bus, slot);
        }
    }
}