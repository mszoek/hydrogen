/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <hw/types.h>

#define CTRL_KEYBOARD   0
#define CTRL_TIMER      1
#define CONTROLLER_MAX  2

extern UInt32 g_controllers[];
extern bool verbose;

char isprint (unsigned char c);
void printdata(UInt8* nodedata, int len);
void displayStatusLine();
void displayStartupMsg(unsigned int size);
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size);

#endif