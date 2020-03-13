/*
 * H2 Kernel system call interface
 * Copyright (C) 2019 Zoe Knox. All rights reserved.
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#include <hw/types.h>

extern "C" int _syscall(void);
UInt64 syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4);

#endif // SYSCALL_H
