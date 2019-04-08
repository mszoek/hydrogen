/*
 * H2 Virtual Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef VMEM_H
#define VMEM_H

#include <hw/types.h>
#include <kmem.h>

/* store PAE page tables in the bss. PML4T entries are PDPT.
 * PDPT entries are PDT. PDT entries are PT. PT entries are
 * physical addresses of 4K blocks */
extern UInt64 pml4t[512] __attribute__((aligned(4096))); // Page Map Level 4 Table. Each entry is 512GB
extern UInt64 pdpt[1024] __attribute__((aligned(4096))); // Page Directory Pointer Table. Each entry is 1GB
extern UInt64 pdt[1024] __attribute__((aligned(4096))); // Page Directory Table. Each entry is 2MB
extern UInt64 pt[32768] __attribute__((aligned(4096)));  // Page Tables. Each entry is a 4K physical block.

const UInt64 KB = 1024;
const UInt64 MB = 1024*1024;
const UInt64 GB = 1024*1024*1024;
const UInt64 HALF_TB = 512ULL*1024ULL*1024ULL*1024ULL;
const UInt64 TB = 1024ULL*1024ULL*1024ULL*1024ULL;

class VirtualMemoryManager
{
public:
	VirtualMemoryManager();
	virtual ~VirtualMemoryManager();

	UInt64 remap(UInt64 phys, UInt64 virt, UInt64 size);
	void *malloc(unsigned int size);
    void free(void *p);

private:
	/* memory pools for small allocs */
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
#define NR_POOLS 9
    poolHeader pools[NR_POOLS];

	// base addr of kernel virtual memory (12 TB)
	const UInt64 kernelVMABase = 0xC0000000000;
};

#endif // VMEM_H