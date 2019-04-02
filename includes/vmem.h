/*
 * H2 Virtual Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>

class VirtualMemoryManager
{
public:
	VirtualMemoryManager();
	virtual ~VirtualMemoryManager();

private:
	UInt32 pageDirectory[1024] __attribute__((aligned(4096)));
};