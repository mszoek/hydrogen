/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <hw/types.h>
#include <kmem.h>

#define KERN_ADDRESS 0x100000 // kernel load address (see loader.asm)

#define CTRL_KEYBOARD   0
#define CTRL_TIMER      1
#define CTRL_SCREEN     2
#define CTRL_PCI        3
#define CTRL_AHCI       4
#define CONTROLLER_MAX  5

typedef struct
{
    UInt8 bus;
    UInt8 slot;
    UInt8 func;
    UInt8 part;
} RootDisk;

extern PhysicalMemoryManager *pmm;
extern UInt32 g_controllers[];
extern bool verbose;

char isprint (unsigned char c);
void printdata(UInt8* nodedata, int len);
void displayStatusLine();
void displayStartupMsg(unsigned int size);

extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size);

void panic();

#endif