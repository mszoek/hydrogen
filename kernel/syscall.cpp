/*
 * H2 Kernel system call interface
 * Copyright (C) 2019 Zoe Knox. All rights reserved.
 */

#include <syscall.h>
#include <syscalls.h>
#include <sched.h>
#include <kstdio.h>
#include <kernel.h>
#include <hw/screen.h>

#define KERNEL_HFS
#include <fs/hfs.h>

extern "C" int _syscall(void)
{
    int nr;
    UInt64 arg0, arg1, arg2, arg3, arg4;

    asm volatile(
        "mov %%r10, %0;"
        "mov %%r11, %1;"
        "mov %%r12, %2;"
        "mov %%r13, %3;"
        "mov %%r14, %4;"
        "mov %%r15, %5;"
        : "=m"(nr),"=m"(arg0),"=m"(arg1),"=m"(arg2),"=m"(arg3),"=m"(arg4)
    );
    return syscall(nr, arg0, arg1, arg2, arg3, arg4);
}

int syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4)
{
    int rc = 0;
    switch(nr)
    {   
        case SYSCALL_WRITE:
            kprint(arg0);
            rc = 0;
            break;
        case SYSCALL_EXIT:
            rc = 0;
            Scheduler::terminateTask();
            break;
        case SYSCALL_STAT:
            if(arg2 == 0)
                rc = rootfs->stat((char *)arg0, (struct stat *)arg1);
            else if(arg2 == 1)
                rc = rootfs->fstat(arg0, (struct stat *)arg1);
            else
                rc = -1;
            break;
        case SYSCALL_FBINFO:
            rc = ((ScreenController *)g_controllers[CTRL_SCREEN])->getFBInfo((struct fbInfo *)arg0);
            break;
        case SYSCALL_OPEN:
            rc = rootfs->open((char *)arg0);
            break;
        case SYSCALL_CLOSE:
            rc = 0;
            rootfs->close(arg0);
            break;
        case SYSCALL_READ:
            rc = rootfs->read(arg0, (UInt8 *)arg1, arg2);
            break;
    }

    return rc;
}
