/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#include <syscall.h>
#include <errno.h>
#include <sys/stat.h>

int stat(const char *path, struct stat *stbuf)
{
    int rc;

    if(path == 0 || *path == 0 || stbuf == 0)
    {
        errno = EINVAL;
        rc = -1;
    } else {
        rc = _syscall( SYSCALL_STAT, (UInt64)path, (UInt64)stbuf, 0, 0, 0);
    }

    if ( rc == -1 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
    }
    return rc;
}

int fstat(int fd, struct stat *stbuf)
{
    int rc;

    if(fd < 0 || stbuf == 0)
    {
        errno = EINVAL;
        rc = -1;
    } else {
        rc = _syscall( SYSCALL_STAT, fd, (UInt64)stbuf, 1, 0, 0);
    }

    if ( rc == -1 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
    }
    return rc;
}
