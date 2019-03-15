#ifndef KERNEL_H
#define KERNEL_H

char isprint (unsigned char c);
void printdata(UInt8* nodedata, int len);
void displayStatusLine();
void displayStartupMsg(unsigned int size);
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size);

#endif