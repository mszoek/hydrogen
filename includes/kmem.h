/*
 * H2 Kernel Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef _KMEM_H
#define _KMEM_H

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

#define MALLOC_MAGIC 0xC0DEBABE

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

    void printStats();
    UInt32 memSize();
    UInt32 memSizeBlocks();
    UInt32 memFree();
    UInt32 memFreeBlocks();
    void *malloc(unsigned int size);
    void free(void *p);

private:
    UInt32 physMemorySize;
    UInt32 physUsedBlocks;
    UInt32 physMaxBlocks;
    UInt32 *physMemoryMap;

    typedef struct __poolNode
    {
        struct __poolNode *prev;
        struct __poolNode *next;
        void *chunk;
    } poolNode;

    typedef struct __mallocHeader
    {
        poolNode *node;
        UInt32 magic;
    } mallocHeader;

    typedef struct __poolHeader
    {
        UInt32 size;
        UInt32 nrFreeChunks;
        poolNode *free;
        poolNode *used;
    } poolHeader;

    // pools are held in a static list by size. grows horizontally.
#define NR_POOLS 8
    poolHeader pools[NR_POOLS];

    inline void pmmBitmapSet(int bit);
    inline void pmmBitmapUnset(int bit);
    inline int pmmBitmapTest(int bit);
    int findFirstFree();
    int findFirstFree(UInt32 size);
    void initRegion(UInt32 base, UInt32 size);
    void dropRegion(UInt32 base, UInt32 size);
    void *allocBlock(); // alloc one block
    void *allocBlock(UInt32 size); // alloc size blocks
    void freeBlock(void *p); // free one block
    void freeBlock(void *p, UInt32 size); // free size blocks
};

/* standard memory functions */
void operator delete(void *p, unsigned long size);

void memcpy(char *dst, char *src, unsigned int len);
void memset(char *dst, char val, int len);

#endif
