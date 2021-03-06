/*
 * H2 PCI Bus Driver
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/types.h>
#include <hw/port_io.h>
#include <hw/pci.h>
#include <hw/ata.h>
#include <hw/screen.h>
#include <kmem.h>
#include <kstdio.h>

PCIController::PCIController()
{
    if(verbose)
        kprintf("hw/PCIController: 0x%x\n", this);
    g_controllers[CTRL_PCI] = (UInt64)this;
    pciTableIndex = 0;
    memset((char *)pciTable, 0, sizeof(pciTable));
}

PCIController::~PCIController()
{
    g_controllers[CTRL_PCI] = 0;
}

UInt16 PCIController::pciReadCfgWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset)
{
    return (UInt16)(pciReadCfgDWord(bus, slot, func, offset) >> ((offset & 2) * 8) & 0xffff);
}

UInt32 PCIController::pciReadCfgDWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset)
{
    UInt32 address;

    /*
    31     30-24    23-16 	 15-11  10-8     7-0
    Enable Reserved  Bus #  Device  Func  Reg Offset 
    */

    address = ((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xfc) | 0x80000000);
    portDWordOut(PCI_CFG_ADDR, address);
    return portDWordIn(PCI_CFG_DATA);
}

void PCIController::pciCheckDevice(UInt32 bus, UInt32 slot)
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

        pciTable[pciTableIndex].bus = bus;
        pciTable[pciTableIndex].slot = slot;
        pciTable[pciTableIndex].function = function;
        pciTable[pciTableIndex].deviceID = device;
        pciTable[pciTableIndex].vendorID = vendor;
        pciTable[pciTableIndex].classCode = (classcode & 0xFF00) >> 8;
        pciTable[pciTableIndex].subclassCode = classcode & 0xFF;
        pciTable[pciTableIndex].headerType = headertype & 0x7f;
        pciTable[pciTableIndex].BIST = (headertype & 0xFF00) >> 8;
        
        UInt16 val = pciReadCfgWord(bus, slot, function, 0xc);
        pciTable[pciTableIndex].latencyTimer = (val & 0xFF00) >> 8;
        pciTable[pciTableIndex].cacheLineSize = val & 0xFF;

    /* read 6 dwords for the BARs. Only header type 0x00 has all - the others have 2 or 0
       so we will be stuffing other data in the BAR space. Can parse it later.
       NOTE: the low bits of BARs need to be masked & 0xFC before using!! Kept
       here so we can distinguish type: low 00 = mem addr, 01 = I/O addr */
        for(int j = 0; j < 6; ++j)
        {
            UInt32 val32 = pciReadCfgDWord(bus, slot, function, 0x10+(4*j));
            pciTable[pciTableIndex].baseAddrReg[j] = val32;
        }

        if(verbose || debug)
        {
            kprintf("%d/%d.%d %x:%x class %x type %x %s\n", bus, slot, function,
                vendor, device, classcode /*& 0x7fff*/, headertype & 0x7f,
                pciClassCodes[((classcode & 0xFF00) >> 8) % 13]);
            if(debug)
            {
                for(int x = 0; x < 6; ++x)
                    kprintf("BAR%d=%x ", x, pciTable[pciTableIndex].baseAddrReg[x]);
                kprintf("\n");
            }
        }
        ++pciTableIndex;
        if(headertype & 0x80 == 0) break;
    }
 }
 
void PCIController::pciEnumBuses(void)
{
    UInt32 bus, slot;

    memset((char *)pciTable, 0xff, sizeof(pciTable));

    if(verbose)
        kprintf("PCI: Enumerating buses\n");

    for(bus = 0; bus < 256; bus++)
    {
        for(slot = 0; slot < 32; slot++)
        {
            pciCheckDevice(bus, slot);
        }
    }
}

void PCIController::startDevices(void)
{
    /* Call this only with interrupts enabled! The timer is required
    to create delays after I/O during ATA init. */

    for(int j = 0; j < 64; j++)
    {
        if(pciTable[j].bus == 0xFFFFFFFF)
            break;

        switch(pciTable[j].classCode)
        {
            case PCI_MASS_STORAGE_CTRL:
            {
                switch(pciTable[j].subclassCode)
                {
                    case 0x6:
                        if(g_controllers[CTRL_AHCI] == 0)
                        {
                            UInt64 addr = vmm->remap(pciTable[j].baseAddrReg[5], 0x40);
                            new AHCIController((hbaMem *)(addr));
                        }
                        break;
                }
                break;
            }

            case PCI_DISPLAY_CTRL:
                break;

            default:
                if(debug)
                    kprintf("PCI: Unsupported device: Vendor 0x%x Device 0x%x Class 0x%x.%x\n",
                        pciTable[j].vendorID, pciTable[j].deviceID, pciTable[j].classCode, pciTable[j].subclassCode);
        }
    }
}