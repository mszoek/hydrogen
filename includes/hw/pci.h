#ifndef HW_PCI_H
#define HW_PCI_H

#define PCI_CFG_ADDR 0xCF8
#define PCI_CFG_DATA 0xCFC

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
    UInt32 baseAddrReg[5];
};

UInt16 pciReadCfgWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset);
UInt32 pciReadCfgDWord(UInt32 bus, UInt32 slot, UInt32 func, UInt32 offset);
void pciEnumBuses(void);


#endif // HW_PCI_H