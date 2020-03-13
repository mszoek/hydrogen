/* _PDCLIB_fillbuffer( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <types.h>
#include <stdio.h>
#include <syscall.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"
#include "errno.h"

typedef long ssize_t;

int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )
{
    /* No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
    ssize_t rc = _syscall( SYSCALL_READ, stream->handle, (UInt64)stream->buffer, stream->bufsize, 0, 0 );
    if ( rc > 0 )
    {
        /* Reading successful. */
        if ( ! ( stream->status & _PDCLIB_FBIN ) )
        {
            /* TODO: Text stream conversion here */
        }
        stream->pos.offset += rc;
        stream->bufend = rc;
        stream->bufidx = 0;
        return 0;
    }
    if ( rc < 0 )
    {
        /* The 1:1 mapping done in _PDCLIB_config.h ensures
           this works.
        */
        *_PDCLIB_errno_func() = errno;
        /* Flag the stream */
        stream->status |= _PDCLIB_ERRORFLAG;
        return EOF;
    }
    /* End-of-File */
    stream->status |= _PDCLIB_EOFFLAG;
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
