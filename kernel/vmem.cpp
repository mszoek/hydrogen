/*
* H2 Virtual Memory Manager
* Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
*/

#include <kernel.h>
#include <kstdio.h>
#include <vmem.h>
#include <sched.h> // for curTask in sbrk()

VirtualMemoryManager::VirtualMemoryManager()
{
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
  // 2 blocks holds 510 node entries + 2K spare. This will never be freed.

  void *initpool = pmm->allocBlock(2);
  UInt8 *initptr = (UInt8 *)initpool;

  int size = 8;
  for(int i = 0; i < NR_POOLS; ++i)
  {
    pools[i].size = size;
    pools[i].used = 0;
    pools[i].nrFreeChunks = 0;

    // allocate one block for this pool
    void *block = pmm->allocBlock();
    memset((char *)block, 0, PMM_BLOCK_SIZE);

    // set up the free list
    pools[i].free = (poolNode *)initptr;
    pools[i].free->prev = 0;
    pools[i].free->next = 0;

    // carve the block into 'size' chunks on the free list
    int count = PMM_BLOCK_SIZE / (size + sizeof(mallocHeader)) - 1;

    pools[i].free->chunk = (UInt8 *)block + (count * (size + sizeof(mallocHeader)));
    pools[i].nrFreeChunks++;
    count--;
    initptr += sizeof(poolNode);

    while(count >= 0)
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
      size = 2032; // +16 byte header gives 2 chunks per 4K block
  }
}

VirtualMemoryManager::~VirtualMemoryManager()
{
}

UInt64 VirtualMemoryManager::unmap(UInt64 virt)
{
  return unmap(virt, (UInt64)pml4t);
}

UInt64 VirtualMemoryManager::unmap(UInt64 virt, UInt64 cr3)
{
	if(virt < 0x100000)
		return virt;	// first 1MB is identity mapped

  UInt64 *mypml4t = (UInt64 *)cr3;

  // find the page table indexes for our virtual addr
  int pml4Idx = (UInt64)(virt / (512UL*GB));
  UInt64 v = (virt - (512*GB*pml4Idx));

  int pdptIdx = v / GB;
  v = v - (pdptIdx*GB);

  int pdtIdx = v / (2*MB);
  v = v - (pdtIdx*2*MB);

  int ptIdx = v / 4096;

  if(pml4t[pml4Idx] == 0) // not mapped if not in table
    return virt;

  UInt64 *mypdpt = (UInt64 *)((mypml4t[pml4Idx] & ~0x0FFF) | KERNEL_VMA);
  if(mypdpt[pdptIdx] == 0) // not mapped if not in table
    return virt;

  UInt64 *mypdt = (UInt64 *)((mypdpt[pdptIdx] & ~0x0FFF) | KERNEL_VMA);
  if(mypdt[pdtIdx] == 0) // not mapped if not in table
    return virt;

  UInt64 *mypt = (UInt64 *)((mypdt[pdtIdx] & ~0x0FFF) | KERNEL_VMA);
  return (mypt[ptIdx] & ~0x0FFF) | (virt & 0x0FFF);


  // if(virt >= VMA_BASE)
  //   return virt - VMA_BASE;
  // else if(virt >= KERNEL_VMA)
  //   return virt - KERNEL_VMA;
  // else
  //   return virt;  
}

UInt64 VirtualMemoryManager::unmap(UInt64 virt, UInt64 size, UInt64 cr3)
{
  // UInt64 phys = unmap(virt);

	if(virt < 0x100000)
		return virt;	// first 1MB is identity mapped

  UInt64 *mypml4t = (UInt64 *)cr3;
	UInt64 orig = virt;
	UInt64 end = virt+size;
  bool first = true;
  UInt64 phys = 0;

	while(virt < end)
	{
		// find the page table indexes for our virtual addr
		int pml4Idx = (UInt64)(virt / (512UL*GB));
		UInt64 v = (virt - (512*GB*pml4Idx));

		int pdptIdx = v / GB;
		v = v - (pdptIdx*GB);

		int pdtIdx = v / (2*MB);
		v = v - (pdtIdx*2*MB);

		int ptIdx = v / 4096;

		if(pml4t[pml4Idx] == 0) // not mapped if not in table
      return virt;

		UInt64 *mypdpt = (UInt64 *)((mypml4t[pml4Idx] & ~0x0FFF) | KERNEL_VMA);
		if(mypdpt[pdptIdx] == 0) // not mapped if not in table
      return virt;

		UInt64 *mypdt = (UInt64 *)((mypdpt[pdptIdx] & ~0x0FFF) | KERNEL_VMA);
		if(mypdt[pdtIdx] == 0) // not mapped if not in table
      return virt;

		UInt64 *mypt = (UInt64 *)((mypdt[pdtIdx] & ~0x0FFF) | KERNEL_VMA);
    if(first)
    {
      phys = (mypt[ptIdx] & ~0x0FFF) | (virt & 0x0FFF);
      first = false;
    }
		mypt[ptIdx] = 0; // mark page absent

		virt += 4096;
  }

  return phys;
}

UInt64 VirtualMemoryManager::remap(UInt64 phys, UInt64 size)
{
	return remap((UInt64)pml4t, phys, size, VMA_BASE+phys);
}

UInt64 VirtualMemoryManager::remap(UInt64 phys, UInt64 size, UInt64 virt)
{
	return remap((UInt64)pml4t, phys, size, virt);
}

UInt64 VirtualMemoryManager::remap(UInt64 cr3, UInt64 phys, UInt64 size, UInt64 virt)
{
	if(phys < 0x100000)
		return phys;	// first 1MB is identity mapped

  UInt64 *mypml4t = (UInt64 *)cr3;
  int perm = 3; // supervisor (ring 0) page
  if(mypml4t != pml4t)
    perm = 7; // user (ring 3) page

	UInt64 orig = virt;
	UInt64 end = virt+size;
	while(virt < end)
	{
		// find the page table indexes for our virtual addr
		int pml4Idx = (UInt64)(virt / (512UL*GB));
		UInt64 v = (virt - (512*GB*pml4Idx));

		int pdptIdx = v / GB;
		v = v - (pdptIdx*GB);

		int pdtIdx = v / (2*MB);
		v = v - (pdtIdx*2*MB);

		int ptIdx = v / 4096;

		if(mypml4t[pml4Idx] == 0)
		{
			// create a new pdpt for this 512GB
			mypml4t[pml4Idx] = (UInt64)pmm->allocBlock();
			memset((UInt32 *)(mypml4t[pml4Idx]+KERNEL_VMA), 0, 1024);
			mypml4t[pml4Idx] |= perm;
		}

		UInt64 *mypdpt = (UInt64 *)((mypml4t[pml4Idx] & ~0x0FFF) | KERNEL_VMA);
		if(mypdpt[pdptIdx] == 0)
		{
			// create a new pdt for this 1GB
			mypdpt[pdptIdx] = (UInt64)pmm->allocBlock();
			memset((UInt32 *)(mypdpt[pdptIdx] | KERNEL_VMA), 0, 1024);
			mypdpt[pdptIdx] |= perm;
		}

		UInt64 *mypdt = (UInt64 *)((mypdpt[pdptIdx] & ~0x0FFF) | KERNEL_VMA);
		if(mypdt[pdtIdx] == 0)
		{
			// create a new pt for this 2MB
			mypdt[pdtIdx] = (UInt64)pmm->allocBlock();
			memset((UInt32 *)(mypdt[pdtIdx] | KERNEL_VMA), 0, 1024);
			mypdt[pdtIdx] |= perm;
		}

		UInt64 *mypt = (UInt64 *)((mypdt[pdtIdx] & ~0x0FFF) | KERNEL_VMA);
		mypt[ptIdx] = phys | perm; // mark page present and writable

		virt += 4096;
		phys += 4096;
	}

	return orig;
}

void *VirtualMemoryManager::malloc(const unsigned int size)
{
  if(size <= 2032)
  {
    for(int i = 0; i < NR_POOLS; ++i)
    {
      // add a block if any pool is low on free chunks
      if(pools[i].nrFreeChunks < 2)
      {
        void *initpool = (void *)remap((UInt64)pmm->allocBlock(2), 2*PMM_BLOCK_SIZE);

        if(initpool != 0)
        {
          // memory for the poolNode structures
          UInt8 *initptr = (UInt8 *)initpool;

          // and a block for this pool
          void *block = initptr + PMM_BLOCK_SIZE;
          memset((char *)block, 0, PMM_BLOCK_SIZE);

          // carve the block into 'size' chunks on the free list
          int count = PMM_BLOCK_SIZE / (pools[i].size + sizeof(mallocHeader)) - 1;
          while(count >= 0)
          {
            poolNode *tmp = (poolNode *)initptr;
            tmp->chunk = (UInt8 *)block + (count * (pools[i].size + sizeof(mallocHeader)));
            tmp->prev = 0;
            tmp->next = pools[i].free;
            pools[i].free->prev = tmp;
            pools[i].free = tmp;

            count--;
            initptr += sizeof(poolNode);
            pools[i].nrFreeChunks++;
          }
          // kprintf("pool %d poolsize %d new free chunks %d\n",i,pools[i].size,pools[i].nrFreeChunks);
        }
      }
      
      if(size <= pools[i].size && pools[i].nrFreeChunks > 0)
      {
        // kprintf("size %d pool %d poolsize %d free %d\n",size,i,
        //   pools[i].size,pools[i].nrFreeChunks);

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
        tmp->magic = ((i & 0xFF) << 24) | (MALLOC_MAGIC & 0xFFFFFF);
        tmp->node = pools[i].used;

        tmp = (mallocHeader *)((UInt64)tmp + sizeof(mallocHeader));
        // kprintf("malloc(%d)=%x p=%x POOL %d\n",size,(UInt32)tmp-sizeof(mallocHeader),tmp,i);
        return (void *)remap((UInt64)tmp, size);
      }
    }
  } else {
    int newsize = size + sizeof(mallocHeader);
    int blocks = newsize / PMM_BLOCK_SIZE + (newsize % PMM_BLOCK_SIZE ? 1 : 0);
    void *p = (void *)remap((UInt64)pmm->allocBlock(blocks), newsize);
    if(p == 0)
      return 0; // out of memory!
    ((mallocHeader *)p)->magic = 0xEE000000 | MALLOC_MAGIC;
    ((mallocHeader *)p)->node = (poolNode *)size; // we need this to free!
    // kprintf("malloc(%d)=%x p=%x blocks=%d magic=%x\n",size,p,(UInt32)p+sizeof(mallocHeader),blocks,((mallocHeader *)p)->magic);
    p = (void *)((UInt64)p + sizeof(mallocHeader));
    return p;
  }

  kprintf("malloc(): cannot alloc %d bytes\n",size);
  return (void *)0;
}

void VirtualMemoryManager::free(void *p)
{
  // first, is this a full block without header or a pool chunk?
  void *hdr = (char *)p - sizeof(mallocHeader);
  UInt32 magic = ((mallocHeader *)hdr)->magic;

  if((magic & 0xFFFFFF) == (MALLOC_MAGIC & 0xFFFFFF))
  {
    int poolID = (magic & 0xFF000000) >> 24;

    if(poolID == 0xEE)
    {
      // this is a full block header
      ((mallocHeader *)hdr)->magic = 0;
      void *q = p;
      p = (void *)((UInt64)p - sizeof(mallocHeader));
      int len = (UInt64)((mallocHeader *)hdr)->node + sizeof(mallocHeader);
      int blocks = len / PMM_BLOCK_SIZE + (len % PMM_BLOCK_SIZE ? 1 : 0);
      // kprintf("free(%d)=%x p=%x blocks %d magic=%x (now 0)\n", len - sizeof(mallocHeader), (UInt32)p, (UInt32)q, blocks, magic);
      if((UInt64)p % PMM_BLOCK_ALIGN)
      {
        // not block aligned? something's weird.
        kprintf("free: freeing %d blocks at %x which is not aligned\n", blocks, (UInt64)p);
      }
      pmm->freeBlock((void *)unmap((UInt64)p), blocks);
      return;
    }

    // not a full block so this is a pool header
    if(poolID < 0 || poolID > NR_POOLS)
    {
      kprintf("free: %x has invalid pool ID %d - leaking memory!\n", p, poolID);
      return;
    }
    ((mallocHeader *)hdr)->magic = 0;

    // remove our chunk's node from the used list
    poolNode *node = ((mallocHeader *)hdr)->node;
    if(node->prev == 0) // this is the list head
    {
      pools[poolID].used = node->next;
      node->next->prev = 0; // new list head
    } else {
      node->prev->next = node->next; // unlink this node
    }

    // and add it to the free list
    pools[poolID].free->prev = node;
    node->next = pools[poolID].free;
    node->prev = 0; // new list head
    pools[poolID].free = node;

    pools[poolID].nrFreeChunks++;
  } else {
    // kprintf("free() %x magic=%x INVALID\n", p, magic);
    kprintf("free: %x invalid malloc header! Memory corrupt or double free?\n",p);
  }  
}

void *VirtualMemoryManager::sbrk(SInt64 increment)
{
  /* We're adding memory to a user process by increasing its data segment.
   * Generally: malloc some bytes, map into contiguous memory above the 
   * current segment end, return the start of the new region
   * 
   * sbrk() should free memory with a negative increment but this one never
   * gives back what was allocated.
   */

  if(increment <= 0)
    return (void *)curTask->brk;

  void *block = malloc(increment);
  if(block == 0)
    return (void *)-1;
  UInt64 brk = curTask->brk;
  remap(curTask->vas, (UInt64)block, increment, brk);
  curTask->brk = brk+increment;
  return (void *)brk;
}