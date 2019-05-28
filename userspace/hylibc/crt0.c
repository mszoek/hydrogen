/*
 * H2 Standard C Library - C runtime init
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#include <stdlib.h>     // exit()
#include <sys/stat.h>   // FD_MAX

extern void exit(int);
extern int main(int argc, char **argv);
extern int *_H2LIBC_fdmap;
extern void _init(void);

int _start(int argc, char **argv)
{
    int i;

    _init();
    for(i = 3; i < FD_MAX; ++i)
        _H2LIBC_fdmap[i] = -1;
    
    // set up stdio, stdout, stderr fds 0, 1, 2
    // these are special. kernel fds start at 3 in userspace.
    _H2LIBC_fdmap[0] = 0;
    _H2LIBC_fdmap[1] = 1;
    _H2LIBC_fdmap[2] = 2;

    i = main(argc, argv);

    // clean up and return exit status
    exit(i);
}
