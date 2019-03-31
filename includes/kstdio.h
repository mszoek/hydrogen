/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef KSTDIO_H
#define KSTDIO_H

#include <kstring.h>
#include <stdarg.h>


void kprintAt(const char *message, int col, int row, char attr);
void kprint(const char *message);
int kprintf(const char* str, ...);
void printdata(UInt8* nodedata, int len);

#endif // KSTDIO_H

