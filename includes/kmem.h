#ifndef _KMEM_H
#define _KMEM_H

#include <drivers/screen.h>
#include <kstring.h>

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

struct regionInfo
{
    UInt32 size;
    UInt32 startLo;
    UInt32 startHi;
    UInt32 sizeLo;
    UInt32 sizeHi;
    UInt32 type;
    UInt32 acpi30;
} __attribute__((packed));

UInt32 pmmMemSize();
UInt32 pmmMemSizeBlocks();
UInt32 pmmMemFree();
UInt32 pmmMemFreeBlocks();
int pmmFindFirstFree();
void pmmInit(UInt32 memSize, UInt32 kernAddr, UInt32 kernSize, struct regionInfo *regions, UInt32 regionsLen);
void pmmInitRegion(UInt32 base, UInt32 size);
void pmmDropRegion(UInt32 base, UInt32 size);
void *pmmAlloc();
void pmmFree(void *p);

void operator delete(void *p, unsigned long size);

void memcpy(char *dst, char *src, unsigned int len);
void memset(char *dst, char val, int len);

#endif
