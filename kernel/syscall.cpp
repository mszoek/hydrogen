/*
 * H2 Kernel system call interface
 * Copyright (C) 2019 Zoe Knox. All rights reserved.
 */

#include <syscall.h>
#include <syscalls.h>
#include <sched.h>
#include <kstdio.h>

void syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4)
{
    // kprintf("SYSCALL(%d) %d %d %d %d %d\n", nr, arg0, arg1, arg2, arg3, arg4);
    switch(nr)
    {
        case SYSCALL_PRINTF:
            kprint(arg0);
            break;
        case SYSCALL_EXIT:
            Scheduler::terminateTask();
            break;
    }
}
