/*
 * H2 Virtual Memory Manager
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

class VirtualMemoryManager {

public:
	VirtualMemoryManager();
	~VirtualMemoryManager();
private:
	UInt32 pageDirectory[1024] __attribute__((aligned(4096)));

};