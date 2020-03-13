/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#include <syscall.h>
#include <errno.h>

void *sbrk(int increment)
{
    void *p = _syscall( SYSCALL_SBRK, increment, 0, 0, 0, 0);
    if((signed long long)p == -1)
        errno = ENOMEM;
    return p;
}
