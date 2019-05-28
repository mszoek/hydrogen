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
#include <stdio.h>

extern int *_H2LIBC_fdmap;

int close(int fd)
{
    int rc;

    if(fd < 0 || fd > FD_MAX)
    {
        errno = EINVAL;
        rc = -1;
    } else {
        int kernfd = _H2LIBC_fdmap[fd];
        if(kernfd == 0) 
            rc = fclose(stdin);
        else if(kernfd == 1)
            rc = fclose(stdout);
        else if(kernfd == 2)
            rc = fclose(stderr);
        else
            rc = _syscall( SYSCALL_CLOSE, kernfd - 3, 0, 0, 0, 0);
    }

    if ( rc == -1 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
    } else {
        _H2LIBC_fdmap[fd] = -1;
    }
    return rc;
}
