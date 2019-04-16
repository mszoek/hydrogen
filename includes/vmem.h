/*
 * H2 Virtual Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef VMEM_H
#define VMEM_H

#include <hw/types.h>
#include <kmem.h>

/* PAE page tables in loader.asm. PML4T entries are PDPT.
 * PDPT entries are PDT. PDT entries are PT. PT entries are
 * physical addresses of 4K blocks */
extern UInt64 pml4t[512] __attribute__((aligned(4096))); // Page Map Level 4 Table. Each entry is 512GB
extern UInt64 pdpt[1024] __attribute__((aligned(4096))); // Page Directory Pointer Table. Each entry is 1GB
extern UInt64 pdt[1536] __attribute__((aligned(4096)));  // Page Directory Table. Each entry is 2MB
extern UInt64 pt[32768] __attribute__((aligned(4096)));  // Page Tables. Each entry is a 4K physical block.

const UInt64 KB = 1024;
const UInt64 MB = 1024*1024;
const UInt64 GB = 1024*1024*1024;
const UInt64 HALF_TB = 512ULL*1024ULL*1024ULL*1024ULL;
const UInt64 TB = 1024ULL*1024ULL*1024ULL*1024ULL;

#define FRAMEBUFFER_VMA	0x7f80000000
#define KERNEL_VMA      0x7C00000000
#define VMA_BASE        0x8000000000

class VirtualMemoryManager
{
public:
	VirtualMemoryManager();
	virtual ~VirtualMemoryManager();

	UInt64 remap(UInt64 phys, UInt64 size);
	UInt64 remap(UInt64 phys, UInt64 size, UInt64 virt);
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