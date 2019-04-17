/*
 * H2 Kernel Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>
#include <kstdio.h>
#include <kstring.h>
#include <kmem.h>
#include <kernel.h>


PhysicalMemoryManager::PhysicalMemoryManager(UInt64 memSize, UInt64 kernAddr, 
  UInt32 kernSize, RegionInfo *regions, UInt32 regionsLen)
{
  // if(verbose)
  //   kprintf("kernel/PhysicalMemoryManager: 0x%x\n", this);

  int i = 0;
  char buf[64];
  RegionInfo *region = regions;

	physMemorySize = memSize;
	physMemoryMap = (UInt32*)(kernAddr + kernSize);
	physMaxBlocks = (memSize*1024) / PMM_BLOCK_SIZE;
	physUsedBlocks = physMaxBlocks;
 
	// By default, all of memory is in use
	memset((char*)physMemoryMap, 0xff, physMaxBlocks / PMM_BLOCKS_PER_BYTE);

  if(regions == 0) return;

  while(region < regions+regionsLen)
  {
    if(i > 0 && region->startLo == 0)
      break;

    /* display region info */
    // if(verbose)
    // {
    //   kprintf("Region %d: start 0x%x, len 0x%x, type %d\n", i,
    //    /*region->startHi,*/ region->startLo, 
    //    /*region->sizeHi,*/ region->sizeLo, region->type);
    // }

    /* init any available regions for our use */
    if(region->type == 1)
    {
      UInt64 addr = region->startHi;
      addr <<= 32;
      addr |= region->startLo;
      UInt64 len = region->sizeHi;
      len <<= 32;
      len |= region->sizeLo;
      initRegion(addr, len);
    }

    ++i;
    region = (RegionInfo *)((UInt64)region + region->size + sizeof(region->size));
  }

  /* mark the kernel memory as in use */
  dropRegion(kernAddr - KERNEL_VMA, kernSize+(physMaxBlocks/PMM_BLOCKS_PER_BYTE));

  /* drop unusable low memory areas */
  dropRegion(0, 0x400); // real mode interrupt vectors
  dropRegion(0x400, 0x100); // bios data area
  dropRegion(0x1000, 0x4000); // low mem page tables
  dropRegion(0x7c00, 0x200); // boot sector
  dropRegion(0x80000, 0x20000); // 128kb extended bios data area
  dropRegion(0xa0000, 0x60000); // 384kb video, ROMs, etc.
  // printStats();
}

PhysicalMemoryManager::~PhysicalMemoryManager()
{
}

void PhysicalMemoryManager::printStats()
{
  kprintf("PMM: %d blocks. Used/reserved: %d blocks. Free: %d blocks\nBitmap addr %x size %x\n",
    physMaxBlocks, physUsedBlocks, physMaxBlocks - physUsedBlocks, physMemoryMap,
    physMemorySize/PMM_BLOCKS_PER_BYTE);
}

inline void PhysicalMemoryManager::pmmBitmapSet(int bit)
{
  physMemoryMap[bit / 32] |= (1 << (bit % 32));
}

inline void PhysicalMemoryManager::pmmBitmapUnset(int bit)
{ 
  physMemoryMap[bit / 32] &= ~(1 << (bit % 32));
}

inline int PhysicalMemoryManager::pmmBitmapTest(int bit)
{
    return physMemoryMap[bit / 32] & (1 << (bit % 32));
}

/* return memory size in KB */
UInt64 PhysicalMemoryManager::memSize()
{
  return physMemorySize;
}

/* return memory size in blocks */
UInt64 PhysicalMemoryManager::memSizeBlocks()
{
  return physMaxBlocks;
}

/* return free memory in KB */
UInt64 PhysicalMemoryManager::memFree()
{
  return (memFreeBlocks() * PMM_BLOCK_SIZE) / 1024;
}

/* return free memory in blocks */
UInt64 PhysicalMemoryManager::memFreeBlocks()
{
  return physMaxBlocks - physUsedBlocks;
}

// find the first free block in our bitmap and return it
int PhysicalMemoryManager::findFirstFree()
{
  UInt32 i;

	for(i = 0; i < memSizeBlocks() / 32; i++)
  {
		if(physMemoryMap[i] != 0xffffffff)
    {
      int j;
			for(j = 0; j < 32; j++)
      {
				int bit = 1 << j;
				if( !(physMemoryMap[i] & bit))
					return i*32 + j;
			}
    }
  } 
	return -1;
}

// find a range of size free blocks in our bitmap and return it
int PhysicalMemoryManager::findFirstFree(UInt32 size)
{
	if(size == 0)
		return -1;

	if (size == 1)
		return findFirstFree();

	for(UInt32 i = 0; i < memSizeBlocks() / 32; i++)
  {
		if(physMemoryMap[i] != 0xffffffff)
    {
			for(int j = 0; j < 32; j++)
      {
				int bit = 1<<j;
				if(!(physMemoryMap[i] & bit))
        {
					int startingBit = i*32 + j;

					UInt32 free = 0; //loop through each bit to see if its enough space
					for(UInt32 count = 0; count <= size; count++)
          {
						if(!pmmBitmapTest(startingBit + count))
							free++;

						if(free == size)
							return i*32 + j;
					}
				}
			}
    }
  }
	return -1;
}

void PhysicalMemoryManager::initRegion(UInt64 base, UInt64 size)
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

void PhysicalMemoryManager::dropRegion(UInt64 base, UInt64 size)
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

void *PhysicalMemoryManager::allocBlock()
{
  int frame;
  UInt64 addr;

	if(memFreeBlocks() <= 0)
		return 0;	// out of memory!
 
	frame = findFirstFree();
 	if (frame == -1)
		return 0;	// out of memory!
 
	pmmBitmapSet(frame);
	addr = frame * PMM_BLOCK_SIZE;
	physUsedBlocks++;
 
	return (void*)addr;
}

void PhysicalMemoryManager::freeBlock(void *p)
{
  UInt64 addr = (UInt64)p;
  int frame = addr / PMM_BLOCK_SIZE;

  pmmBitmapUnset(frame);
  physUsedBlocks--;
}

void* PhysicalMemoryManager::allocBlock(UInt32 size)
{
	if(memFreeBlocks() <= size)
		return 0;

	int frame = findFirstFree(size);
	if(frame == -1)
		return 0;

	for(UInt32 i = 0; i < size; i++)
		pmmBitmapSet(frame + i);

	UInt64 addr = frame * PMM_BLOCK_SIZE;
	physUsedBlocks += size;

	return (void*)addr;
}

void PhysicalMemoryManager::freeBlock(void* p, UInt32 size)
{
	UInt64 addr = (UInt64)p;
	int frame = addr / PMM_BLOCK_SIZE;

	for(UInt32 i = 0; i < size; i++)
		pmmBitmapUnset(frame + i);

	physUsedBlocks -= size;
}

void *operator new(unsigned long size)
{
  return vmm->malloc(size);
}

void operator delete(void *p, unsigned long size)
{
  vmm->free(p);
}

void *malloc(const unsigned int size)
{
  return vmm->malloc(size);
}

void free(void *p)
{
  return vmm->free(p);
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

void memset(UInt32 *dst, UInt32 val, int len)
{
  UInt32 *tmp=dst;
  for(;len > 0; --len)
  {
    *tmp++ = val;
  }
}

int memcmp(char *a, char *b, int len)
{
  int i = 0;
  while(i < len)
  {
    if(*(a+i) > *(b+i)) return -1;
    if(*(a+i) < *(b+i)) return 1;
    ++i;
  }
  return 0;
}