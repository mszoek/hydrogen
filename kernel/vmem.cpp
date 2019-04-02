/*
 * H2 Virtual Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <vmem.h>

VirtualMemoryManager::VirtualMemoryManager()
{
	// Wipe our page table
	for(int i = 0; i < 1024; ++i)
	{
		/* Flags for the pages:
			Supervisor: Only kernel-mode can access them
			Write Enabled: Can be read/written to
			Not Present: The page table is not present*/
			
		pageDirectory[i] = 0x00000002;
	}
}

VirtualMemoryManager::~VirtualMemoryManager()
{
}
