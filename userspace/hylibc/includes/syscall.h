/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#ifndef H2_SYSCALL_H
#define H2_SYSCALL_H

#include <types.h>
#include <syscalls.h> 

int _syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4);

#endif /* H2_SYSCALL_H */
