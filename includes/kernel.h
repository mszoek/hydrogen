#ifndef KERNEL_H
#define KERNEL_H

#include <hw/types.h>

#define CTRL_KEYBOARD 0
#define CONTROLLER_MAX 1

extern UInt32 g_controllers[];
extern bool verbose;

char isprint (unsigned char c);
void printdata(UInt8* nodedata, int len);
void displayStatusLine();
void displayStartupMsg(unsigned int size);
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size);

#endif