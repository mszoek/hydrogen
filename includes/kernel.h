/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <hw/types.h>
#include <kmem.h>
#include <bootinfo.h>

#define KERN_ADDRESS 0x100000 // kernel load address (see loader.asm)

#define CTRL_KEYBOARD   0
#define CTRL_TIMER      1
#define CTRL_SCREEN     2
#define CTRL_PCI        3
#define CTRL_AHCI       4
#define CONTROLLER_MAX  5

extern PhysicalMemoryManager *pmm;
extern UInt32 g_controllers[];
extern bool verbose;
extern bool debug;
extern struct multiboot_info bootinfo;

extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size);

char isprint (unsigned char c);
void printdata(UInt8* nodedata, int len);
void displayStatusLine();
void displayStartupMsg(unsigned int size);

void panic();

#endif