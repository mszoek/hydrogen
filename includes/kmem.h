/*
 * H2 Kernel Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef _KMEM_H
#define _KMEM_H

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

class PhysicalMemoryManager
{
public:
    typedef struct
    {
        UInt32 size;
        UInt32 startLo;
        UInt32 startHi;
        UInt32 sizeLo;
        UInt32 sizeHi;
        UInt32 type;
        UInt32 acpi30;
    } __attribute__((packed)) RegionInfo;

    PhysicalMemoryManager(UInt32 memSize, UInt32 kernAddr, UInt32 kernSize,
        RegionInfo *regions, UInt32 regionsLen);
    virtual ~PhysicalMemoryManager();

    UInt32 memSize();
    UInt32 memSizeBlocks();
    UInt32 memFree();
    UInt32 memFreeBlocks();
    void *alloc();
    void free(void *p);

private:
    UInt32 physMemorySize;
    UInt32 physUsedBlocks;
    UInt32 physMaxBlocks;
    UInt32 *physMemoryMap;

    inline void pmmBitmapSet(int bit);
    inline void pmmBitmapUnset(int bit);
    inline int pmmBitmapTest(int bit);
    int findFirstFree();
    void initRegion(UInt32 base, UInt32 size);
    void dropRegion(UInt32 base, UInt32 size);
};

/* standard memory functions */
void operator delete(void *p, unsigned long size);

void memcpy(char *dst, char *src, unsigned int len);
void memset(char *dst, char val, int len);

#endif
