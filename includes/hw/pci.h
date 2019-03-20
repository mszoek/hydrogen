/*
 * H2 PCI Bus Driver
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#ifndef HW_PCI_H
#define HW_PCI_H

#define PCI_CFG_ADDR 0xCF8
#define PCI_CFG_DATA 0xCFC

#define PCI_UNCLASSIFIED 0x00
#define PCI_MASS_STORAGE_CTRL 0x01
#define PCI_NETWORK_CTRL 0x02
#define PCI_DISPLAY_CTRL 0x03
#define PCI_MULTIMEDIA_CTRL 0x04
#define PCI_MEMORY_CTRL 0x05
#define PCI_BRIDGE_DEVICE 0x06
#define PCI_SIMPLE_COMM_CTRL 0x07
#define PCI_BASE_SYSTEM_PERIPH 0x08
#define PCI_INPUT_DEV_CTRL 0x09
#define PCI_DOCKING_STN 0x0A
#define PCI_PROCESSOR 0x0B
#define PCI_SERIAL_BUS_CTRL 0x0C
#define PCI_WIRELESS_CTRL 0x0D

struct pciDeviceEntry
{
    UInt32 bus;
    UInt32 slot;
    UInt32 function;
    UInt16 deviceID;
    UInt16 vendorID;
    UInt8 classCode;
    UInt8 subclassCode;
    UInt8 progIF;
    UInt8 revisionID;
    UInt8 BIST;
    UInt8 headerType;
    UInt8 latencyTimer;
    UInt8 cacheLineSize;
    UInt32 baseAddrReg[6];
};
extern struct pciDeviceEntry pciTable[64];

UInt16 pciReadCfgWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset);
UInt32 pciReadCfgDWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset);
void pciEnumBuses(void);


#endif // HW_PCI_H