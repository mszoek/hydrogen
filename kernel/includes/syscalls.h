/*
 * H2 Kernel system calls list
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYSCALL_EXIT 1
#define SYSCALL_WRITE 2
#define SYSCALL_STAT 3
#define SYSCALL_FBINFO 4
#define SYSCALL_OPEN 5
#define SYSCALL_CLOSE 6
#define SYSCALL_SEEK 7 /* FIXME: not impl */
#define SYSCALL_READ 8 /* FIXME: handle reading from offset into file */
#define SYSCALL_RENAME 9 /* FIXME: not impl */
#define SYSCALL_UNLINK 10 /* FIXME: not impl */
#define SYSCALL_SBRK 11
#define SYSCALL_RTCREAD 12

#define SYSCALL_EXEC 13

#define NR_SYSCALLS 13

#endif // SYSCALLS_H
