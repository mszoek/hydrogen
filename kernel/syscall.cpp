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
#include <hw/rtc.h>
#include <hw/keyboard.h>
#include <errno.h>

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

UInt64 syscall(int nr, UInt64 arg0, UInt64 arg1, UInt64 arg2, UInt64 arg3, UInt64 arg4)
{
    UInt64 rc = 0;
    UInt64 bufaddr = 0;

    switch(nr)
    {
        case SYSCALL_WRITE:
            /* FIXME: do proper write! arg0: fd, arg1: buffer, arg2: length */
            // map the buffer into kernel memory (it's only in user page tables)
            bufaddr = vmm->unmap(arg1, curTask->vas);
            bufaddr = vmm->remap(bufaddr, arg2);

            rc = arg2; // return number of bytes written
            if(arg0 > 0 && arg0 < 3) /* stdout or stderr */
                kwrite((const char *)bufaddr, arg2);
            else if(arg0 == 0) /* stdin */
                rc = -EBADF;
            else
                kprintf("syscall write: %d,%x,%d",arg0 - 3,bufaddr,arg2);

            vmm->unmap(bufaddr, arg2, (UInt64)pml4t); // remove from kernel page tables
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
                rc = -EINVAL;
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
            /* FIXME: do proper read! Userspace fds are adjusted by 3. 0 is 
             * alway stdin. 1 = stdout, 2 = stderr. FD 3+ are kernel fds 0+
             */
            // map the buffer into kernel memory (it's only in user page tables)
            bufaddr = vmm->unmap(arg1, curTask->vas);
            bufaddr = vmm->remap(bufaddr, arg2);

            if(arg0 == 0) /* stdin */
            {
                KeyboardController *kbd = (KeyboardController *)g_controllers[CTRL_KEYBOARD];
                rc = kbd->getKeyboardBuffer((UInt8 *)bufaddr, arg2);
                rc = kbd->translateCodes((UInt8 *)bufaddr, rc);

                while(rc == 0) /* nothing in buffer? block. */
                {
                    lock();
                    Scheduler::updateTimeUsed();
                    curTask->next = waitQ;
                    waitQ = curTask;
                    Scheduler::blockTask(waitIO);
                    unlock();
                    rc = kbd->getKeyboardBuffer((UInt8 *)bufaddr, arg2);
                    rc = kbd->translateCodes((UInt8 *)bufaddr, rc);
                }
            }
            else if(arg0 > 0 && arg0 < 3) /* stdout or stderr */
                rc = -EBADF;
            else
                rc = rootfs->read(arg0 - 3, (UInt8 *)arg1, arg2);
            vmm->unmap(bufaddr, arg2, (UInt64)pml4t); // remove from kernel page tables
            break;
        case SYSCALL_SBRK:
            rc = (UInt64)vmm->sbrk(arg0);
            break;
        case SYSCALL_RTCREAD:
            rc = (UInt64)rtcRead();
            break;
    }

    return rc;
}
