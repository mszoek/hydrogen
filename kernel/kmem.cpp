/*
 * H2 Kernel Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>
#include <kstdio.h>
#include <kstring.h>
#include <kmem.h>
#include <kernel.h>


PhysicalMemoryManager::PhysicalMemoryManager(UInt32 memSize, UInt32 kernAddr, 
  UInt32 kernSize, RegionInfo *regions, UInt32 regionsLen)
{
  if(verbose)
    kprintf("kernel/PhysicalMemoryManager: 0x%x\n", this);

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
    if(verbose)
    {
      kprintf("Region %d: start 0x%x, len 0x%x, type %d\n", i,
       /*region->startHi,*/ region->startLo, 
       /*region->sizeHi,*/ region->sizeLo, region->type);
    }

    /* init any available regions for our use */
    if(region->type == 1)
    {
      initRegion(region->startLo, region->sizeLo);
    }

    ++i;
    region = (RegionInfo *)((UInt32)region + region->size + sizeof(region->size));
  }

  /* mark the kernel memory as in use */
  dropRegion(kernAddr, kernSize+regionsLen);

  /* drop unusable low memory areas */
  dropRegion(0, 0x400); // real mode interrupt vectors
  dropRegion(0x400, 0x100); // bios data area
  dropRegion(0x7c00, 0x200); // boot sector
  dropRegion(0x80000, 0x20000); // 128kb extended bios data area
  dropRegion(0xa0000, 0x60000); // 384kb video, ROMs, etc.

  kprintf("PMM initialized: %d blocks. Used/reserved: %d blocks. Free: %d blocks\n",
    physMaxBlocks, physUsedBlocks, physMaxBlocks - physUsedBlocks);
}

PhysicalMemoryManager::~PhysicalMemoryManager()
{
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
UInt32 PhysicalMemoryManager::memSize()
{
  return physMemorySize;
}

/* return memory size in blocks */
UInt32 PhysicalMemoryManager::memSizeBlocks()
{
  return physMaxBlocks;
}

/* return free memory in KB */
UInt32 PhysicalMemoryManager::memFree()
{
  return (memFreeBlocks() * PMM_BLOCK_SIZE) / 1024;
}

/* return free memory in blocks */
UInt32 PhysicalMemoryManager::memFreeBlocks()
{
  return physMaxBlocks - physUsedBlocks;
}


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
					return i*4*8 + j;
			}
    }
  } 
	return -1;
}

void PhysicalMemoryManager::initRegion(UInt32 base, UInt32 size)
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

void PhysicalMemoryManager::dropRegion(UInt32 base, UInt32 size)
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

void *PhysicalMemoryManager::alloc()
{
  int frame;
  UInt32 addr;

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

void PhysicalMemoryManager::free(void *p)
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
