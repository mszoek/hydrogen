/* int64_t _PDCLIB_seek( FILE *, int64_t, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <syscall.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"
#include "errno.h"

_PDCLIB_int64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int64_t offset, int whence )
{
    _PDCLIB_int64_t rc;
    switch ( whence )
    {
        case SEEK_SET:
        case SEEK_CUR:
        case SEEK_END:
            /* EMPTY - OK */
            break;
        default:
            *_PDCLIB_errno_func() = _PDCLIB_EINVAL;
            return EOF;
            break;
    }
    rc = _syscall( SYSCALL_SEEK, stream->handle, offset, whence, 0, 0 );
    if ( rc != EOF )
    {
        stream->ungetidx = 0;
        stream->bufidx = 0;
        stream->bufend = 0;
        stream->pos.offset = rc;
        return rc;
    }
    /* The 1:1 mapping in _PDCLIB_config.h ensures that this works. */
    *_PDCLIB_errno_func() = errno;
    return EOF;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
