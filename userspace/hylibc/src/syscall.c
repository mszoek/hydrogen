/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#include <syscall.h>
#include <errno.h>

int _syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4)
{
    if(nr == 0 || nr > NR_SYSCALLS)
    {
      errno = EBADSYSCALL;
      return -EBADSYSCALL;
    }

    asm(
      "movq %0, %%r10;"
      "movq %1, %%r11;"
      "movq %2, %%r12;"
      "movq %3, %%r13;"
      "movq %4, %%r14;"
      "movq %5, %%r15;"
      "int $0x80"
      : : "m"(nr),"m"(arg0),"m"(arg1),"m"(arg2),"m"(arg3),"m"(arg4)
      : "r10","r11","r12","r13","r14","r15"
    );
    errno = 0;
    return 0;
}
