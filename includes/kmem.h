/*
 * H2 Kernel Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef _KMEM_H
#define _KMEM_H

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

#define MALLOC_MAGIC 0x00ADECAF

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

    PhysicalMemoryManager(UInt64 memSize, UInt64 kernAddr, UInt32 kernSize,
        RegionInfo *regions, UInt32 regionsLen);
    virtual ~PhysicalMemoryManager();

    void printStats();
    UInt64 memSize();
    UInt64 memSizeBlocks();
    UInt64 memFree();
    UInt64 memFreeBlocks();
    void *allocBlock(); // alloc one block
    void *allocBlock(UInt32 size); // alloc size blocks
    void freeBlock(void *p); // free one block
    void freeBlock(void *p, UInt32 size); // free size blocks
    void dropRegion(UInt64 base, UInt64 size); // allow drivers to reserve memory areas

private:
    UInt32 physMemorySize;
    UInt32 physUsedBlocks;
    UInt32 physMaxBlocks;
    UInt32 *physMemoryMap;

    inline void pmmBitmapSet(int bit);
    inline void pmmBitmapUnset(int bit);
    inline int pmmBitmapTest(int bit);
    int findFirstFree();
    int findFirstFree(UInt32 size);
    void initRegion(UInt64 base, UInt64 size);
};

/* standard memory functions */
void *operator new(unsigned long size);
void operator delete(void *p, unsigned long size);

void *malloc(unsigned int size);
void free(void *p);

void memcpy(char *dst, char *src, unsigned int len);
void memset(char *dst, char val, int len);
void memset(UInt32 *dst, UInt32 val, int len);
int memcmp(char *a, char *b, int len);

#endif
