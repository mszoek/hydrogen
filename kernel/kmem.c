/* H2OS Kernel memory management
 * Zoe Knox 2017-2019
 */

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

static UInt32 physMemorySize = 0;
static UInt32 physUsedBlocks = 0;
static UInt32 physMaxBlocks = 0;
static UInt32 *physMemoryMap = 0;

inline void pmmBitmapSet(int bit)
{
  physMemoryMap[bit / 32] |= (1 << (bit % 32));
}

inline void pmmBitmapUnset(int bit)
{ 
  physMemoryMap[bit / 32] &= ~(1 << (bit % 32));
}

inline int pmmBitmapTest(int bit)
{
  return physMemoryMap[bit / 32] & (1 << (bit % 32));
}

/* return memory size in blocks */
UInt32 pmmMemSizeBlocks()
{
  return physMemorySize / PMM_BLOCK_SIZE;
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
				if (! (_mmngr_memory_map[i] & bit) )
					return i*4*8+j;
			}
    }
  }
 
	return -1;
}

void	PMM_init (size_t memSize, physical_addr bitmap) {
 
	_mmngr_memory_size	=	memSize;
	_mmngr_memory_map	=	(UInt32*) bitmap;
	_mmngr_max_blocks	=	(PMM_get_memory_size()*1024) / PMM_BLOCK_SIZE;
	_mmngr_used_blocks	=	PMM_get_block_count();
 
	//! By default, all of memory is in use
	memset (_mmngr_memory_map, 0xf, PMM_get_block_count() / PMM_BLOCKS_PER_BYTE );
}

void	PMM_init_region (physical_addr base, size_t size) {
 
	int align = base / PMM_BLOCK_SIZE;
	int blocks = size / PMM_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_unset (align++);
		_mmngr_used_blocks--;
	}
 
	mmap_set (0);	//first block is always set. This insures allocs cant be 0
}

void	PMM_deinit_region (physical_addr base, size_t size) {
 
	int align = base / PMM_BLOCK_SIZE;
	int blocks = size / PMM_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_set (align++);
		_mmngr_used_blocks++;
	}
}

void*	PMM_alloc_block () {
 
	if (PMM_get_free_block_count() <= 0)
		return 0;	//out of memory
 
	int frame = mmap_first_free ();
 
	if (frame == -1)
		return 0;	//out of memory
 
	mmap_set (frame);
 
	physical_addr addr = frame * PMM_BLOCK_SIZE;
	_mmngr_used_blocks++;
 
	return (void*)addr;
}

    void	PMM_free_block (void* p) {
     
    	physical_addr addr = (physical_addr)p;
    	int frame = addr / PMM_BLOCK_SIZE;
     
    	mmap_unset (frame);
     
    	_mmngr_used_blocks--;
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
