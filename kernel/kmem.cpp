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

  /*
   * We're going to have pools for allocations < PMM_BLOCK_SIZE/2. A block 
   * (4K) is subdivided into 'chunks' of fixed size for each pool. Each pool
   * maintains lists of allocated and free chunks. Each pool header indicates
   * the number of 'size' chunks available in the pool.
   * 
   * Blocks in a pool are never freed once allocated so we don't track them.
   * 
   * This scheme isn't efficient for chunks of PMM_BLOCK_SIZE/2 to
   * PMM_BLOCK_SIZE. We just allocate a full block for anything over half.
   */

  // First, allocate a special pool so we can alloc our linked lists
  // 8 blocks = ~2700 node entries. This will never be freed.

  void *initpool = allocBlock(8);
  UInt8 *initptr = (UInt8 *)initpool;

  int size = 8;
  for(i = 0; i < NR_POOLS; ++i)
  {
    pools[i].size = size;
    pools[i].used = 0;
    pools[i].nrFreeChunks = 0;

    // allocate one block for this pool
    void *block = allocBlock();
    memset((char *)block, 0, PMM_BLOCK_SIZE);

    // set up the free list
    pools[i].free = (poolNode *)initptr;
    pools[i].free->prev = 0;
    pools[i].free->next = 0;

    // carve the block into 'size' chunks on the free list
    int count = PMM_BLOCK_SIZE / (size + sizeof(mallocHeader));

    pools[i].free->chunk = (UInt8 *)block + (count * (size + sizeof(mallocHeader)));
    pools[i].nrFreeChunks++;
    count--;
    initptr += sizeof(poolNode);

    while(count > 0)
    {
      poolNode *tmp = (poolNode *)initptr;
      tmp->chunk = (UInt8 *)block + (count * (size + sizeof(mallocHeader)));
      tmp->prev = 0;
      tmp->next = pools[i].free;
      pools[i].free->prev = tmp;
      pools[i].free = tmp;

      count--;
      initptr += sizeof(poolNode);
      pools[i].nrFreeChunks++;
    }

    size *= 2;
    if(size >= 2048)
      size = 2047;
  }
  printStats();
}

PhysicalMemoryManager::~PhysicalMemoryManager()
{
}

void PhysicalMemoryManager::printStats()
{
  kprintf("PMM: %d blocks. Used/reserved: %d blocks. Free: %d blocks\n",
    physMaxBlocks, physUsedBlocks, physMaxBlocks - physUsedBlocks);
  for(int i = 0; i < NR_POOLS; ++i)
  {
    kprintf("Pool %d: chunk size %d bytes, %d chunks free\n", i, 
      pools[i].size, pools[i].nrFreeChunks);
  }
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
					return i*4*8 + j;
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
					int startingBit = i*32;
					startingBit += bit; //get the free bit in the dword at index i

					UInt32 free = 0; //loop through each bit to see if its enough space
					for(UInt32 count = 0; count <= size; count++)
          {
						if(!pmmBitmapTest(startingBit + count))
							free++;

						if(free == size)
							return i*4*8+j;
					}
				}
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

void *PhysicalMemoryManager::allocBlock()
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

void PhysicalMemoryManager::freeBlock(void *p)
{
  UInt32 addr = (UInt32)p;
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

	UInt32 addr = frame * PMM_BLOCK_SIZE;
	physUsedBlocks += size;

	return (void*)addr;
}

void PhysicalMemoryManager::freeBlock(void* p, UInt32 size)
{
	UInt32 addr = (UInt32)p;
	int frame = addr / PMM_BLOCK_SIZE;

	for(UInt32 i = 0; i < size; i++)
		pmmBitmapUnset(frame + i);

	physUsedBlocks -= size;
}

void operator delete(void *p, unsigned long size)
{
  kprintf("FIXME! delete(0x%x, 0x%x)\n",(UInt32)p,size);
}

void *PhysicalMemoryManager::malloc(const unsigned int size)
{
  if(size < (PMM_BLOCK_SIZE / 2))
  {
    for(int i = 0; i < NR_POOLS; ++i)
    {
      if(size <= pools[i].size && pools[i].nrFreeChunks > 0)
      {
        kprintf("size %d pool %d poolsize %d free %d\n",size,i,
          pools[i].size,pools[i].nrFreeChunks);

        // This pool has free chunks. Take the first element from the free
        // list and move it to the used list.
        poolNode *node = pools[i].free;
        pools[i].free = node->next;
        pools[i].free->prev = 0; // new head of list

        pools[i].nrFreeChunks--;

        // insert at beginning of used list
        node->next = pools[i].used;
        node->prev = 0;
        pools[i].used = node;

        mallocHeader *tmp = (mallocHeader *)(node->chunk);
        tmp->magic = MALLOC_MAGIC;
        tmp->node = pools[i].used;

        return (void *)(tmp+sizeof(mallocHeader));
      }
    }
  } else {
    return allocBlock(size / PMM_BLOCK_SIZE + (size % PMM_BLOCK_SIZE ? 1 : 0));
  }
}

void PhysicalMemoryManager::free(void *p)
{
  return;
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
