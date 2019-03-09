/* H2OS Kernel memory management
 * Zoe Knox 2017-2019
 */

#include "hw/types.h"
#include "kmem.h"

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

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
  return physMemorySize / PMM_BLOCK_SIZE;
}

/* return free memory in KB */
UInt32 pmmMemFree()
{
  return (physMemorySize*1024 - (physUsedBlocks*PMM_BLOCK_SIZE)) / 1024;
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
					return i*4*8+j;
			}
    }
  } 
	return -1;
}

void pmmInit(UInt32 memSize, UInt32 bitmap)
{
	physMemorySize = memSize;
	physMemoryMap = (UInt32*)bitmap;
	physMaxBlocks = (pmmMemSize()*1024) / PMM_BLOCK_SIZE;
	physUsedBlocks = pmmMemSizeBlocks();
 
	// By default, all of memory is in use
	memset((char*)physMemoryMap, 0xf, pmmMemSizeBlocks() / PMM_BLOCKS_PER_BYTE);
}

void pmmInitRegion(UInt32 base, UInt32 size)
{ 
	int align = base / PMM_BLOCK_SIZE;
	int blocks = size / PMM_BLOCK_SIZE;
 
	for (; blocks > 0; blocks--)
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
 
	for(; blocks > 0; blocks--)
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
