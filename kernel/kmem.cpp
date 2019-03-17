/* H2OS Kernel memory management
 * Zoe Knox 2017-2019
 */

#include "hw/types.h"
#include "kmem.h"

extern bool verbose;

static UInt32 physMemorySize = 0;
static UInt32 physUsedBlocks = 0;
static UInt32 physMaxBlocks = 0;
static UInt32 *physMemoryMap = 0;


static inline void pmmBitmapSet(int bit)
{
  physMemoryMap[bit / 32] |= (1 << (bit % 32));
}

static inline void pmmBitmapUnset(int bit)
{ 
  physMemoryMap[bit / 32] &= ~(1 << (bit % 32));
}

static inline int pmmBitmapTest(int bit)
{
    return physMemoryMap[bit / 32] & (1 << (bit % 32));
}

/* return memory size in KB */
UInt32 pmmMemSize()
{
  return physMemorySize;
}

/* return memory size in blocks */
UInt32 pmmMemSizeBlocks()
{
  return physMaxBlocks;
}

/* return free memory in KB */
UInt32 pmmMemFree()
{
  return (pmmMemFreeBlocks() * PMM_BLOCK_SIZE) / 1024;
}

/* return free memory in blocks */
UInt32 pmmMemFreeBlocks()
{
  return physMaxBlocks - physUsedBlocks;
}

int pmmFindFirstFree()
{
  UInt32 i;

	for(i = 0; i < pmmMemSizeBlocks() / 32; i++)
  {
		if(physMemoryMap[i] != 0xffffffff)
    {
      int j;
			for(j = 0; j < 32; j++)
      {
				int bit = 1 << j;
				if( !(physMemoryMap[i] & bit))
					return i*4*8 + j;
			}
    }
  } 
	return -1;
}

void pmmInit(UInt32 memSize, UInt32 kernAddr, UInt32 kernSize, struct regionInfo *regions, UInt32 regionsLen)
{
  int i = 0;
  char buf[64];
  struct regionInfo *region = regions;

	physMemorySize = memSize;
	physMemoryMap = (UInt32*)(kernAddr + kernSize);
	physMaxBlocks = (pmmMemSize()*1024) / PMM_BLOCK_SIZE;
	physUsedBlocks = physMaxBlocks;
 
	// By default, all of memory is in use
	memset((char*)physMemoryMap, 0xff, physMaxBlocks / PMM_BLOCKS_PER_BYTE);

  if(regions == 0) return;

  while(region < regions+regionsLen)
  {
    if(i > 0 && region->startLo == 0)
      break;

    /* display region info */
    if(verbose)
    {
      kprintf("Region %d: start 0x%x, len 0x%x, type %d\n", i,
       /*region->startHi,*/ region->startLo, 
       /*region->sizeHi,*/ region->sizeLo, region->type);
    }

    /* init any available regions for our use */
    if(region->type == 1)
    {
      pmmInitRegion(region->startLo, region->sizeLo);
    }

    ++i;
    region = (struct regionInfo *)((UInt32)region + region->size + sizeof(region->size));
  }

  /* mark the kernel memory as in use */
  pmmDropRegion(kernAddr, kernSize+regionsLen);

  /* drop unusable low memory areas */
  pmmDropRegion(0, 0x400); // real mode interrupt vectors
  pmmDropRegion(0x400, 0x100); // bios data area
  pmmDropRegion(0x7c00, 0x200); // boot sector
  pmmDropRegion(0x80000, 0x20000); // 128kb extended bios data area
  pmmDropRegion(0xa0000, 0x60000); // 384kb video, ROMs, etc.

  kprintf("PMM initialized: %d blocks. Used/reserved: %d blocks. Free: %d blocks\n",
    physMaxBlocks, physUsedBlocks, physMaxBlocks - physUsedBlocks);
}

void pmmInitRegion(UInt32 base, UInt32 size)
{ 
	int align = base / PMM_BLOCK_SIZE;
	int blocks = size / PMM_BLOCK_SIZE;

  if(blocks == 0) blocks = 1;

  // kprintf("initRegion(%x, %x) align=%x blocks=%x\n",base,size,align,blocks);
	for (; blocks >= 0; blocks--)
  {
		pmmBitmapUnset(align++);
		physUsedBlocks--;
	}
	pmmBitmapSet(0);	// First block is always set so allocs can't be 0
}

void pmmDropRegion(UInt32 base, UInt32 size)
{
	int align = base / PMM_BLOCK_SIZE;
	int blocks = size / PMM_BLOCK_SIZE;

  if(blocks == 0) blocks = 1;

  // kprintf("dropRegion(%x, %x) align=%x blocks=%x\n",base,size,align,blocks); 
	for(; blocks >= 0; blocks--)
  {
		pmmBitmapSet(align++);
		physUsedBlocks++;
	}
}

void *pmmAlloc()
{
  int frame;
  UInt32 addr;

	if(pmmMemFreeBlocks() <= 0)
		return 0;	// out of memory!
 
	frame = pmmFindFirstFree();
 	if (frame == -1)
		return 0;	// out of memory!
 
	pmmBitmapSet(frame);
	addr = frame * PMM_BLOCK_SIZE;
	physUsedBlocks++;
 
	return (void*)addr;
}

void pmmFree(void *p)
{
  UInt32 addr = (UInt32)p;
  int frame = addr / PMM_BLOCK_SIZE;

  pmmBitmapUnset(frame);
  physUsedBlocks--;
}


void operator delete(void *p, unsigned long size)
{
  kprintf("FIXME! delete(0x%x, 0x%x)\n",(UInt32)p,size);
}


void memcpy(char *dst, char *src, unsigned int len)
{
  int i;
  for(i=0; i<len; ++i)
  {
    *(dst+i) = *(src+i);
  }
}

void memset(char *dst, char val, int len)
{
  char *tmp=dst;
  for(;len > 0; --len)
  {
    *tmp++ = val;
  }
}
