/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#include <syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

// map kernel FDs to process FDs
static int __H2LIBC_fdmap[FD_MAX];
int *_H2LIBC_fdmap = __H2LIBC_fdmap;

static int firstFreeFD(int kernfd)
{
    for(int i = 0; i < FD_MAX; ++i)
        if(_H2LIBC_fdmap[i] == -1)
        {
            _H2LIBC_fdmap[i] = kernfd + 3;
            return i;
        }
    errno = ENFILE; // too many open files
    return -1;
}

int open(const char *path, int flags, ...)
{
    int rc = 0;
    int mode = 0;

    if(path == 0 || *path == 0)
    {
        errno = EINVAL;
        rc = -1;
    }

    switch(flags & (O_RDWR | O_RDONLY | O_WRONLY))
    {
        case O_RDONLY:
        case O_WRONLY:
        case O_RDWR:
            rc = 0;
            break;
        default:
            rc = -1; 
    }

    if(flags & O_CREAT)
    {
        va_list ap;
        va_start( ap, flags );
        mode = va_arg(ap, int);
        va_end( ap );
    }

    if(rc == 0)
        rc = _syscall( SYSCALL_OPEN, (UInt64)path, flags, mode, 0, 0);

    if ( rc == -1 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
    } else {
        int fd = firstFreeFD(rc);
        rc = fd;
    }
    return rc;
}
