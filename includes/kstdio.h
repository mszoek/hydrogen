#ifndef KSTDIO_H
#define KSTDIO_H

#include <kstring.h>
#include <stdarg.h>


void kprintAt(const char *message, int col, int row, char attr);
void kprint(const char *message);
int kprintf(const char* str, ...);

#endif // KSTDIO_H

