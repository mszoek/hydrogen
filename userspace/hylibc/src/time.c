/* time( time_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <types.h>
#include <time.h>
#include <syscall.h>

#ifndef REGTEST

#include "sys/time.h"

/* See comments in time.h on the semantics of time_t. */

time_t time( time_t * timer )
{
    UInt64 now = _syscall(SYSCALL_RTCREAD, 0, 0, 0, 0, 0);
    if ( now > 0 )
    {
        if ( timer != NULL )
        {
            *timer = now;
        }
        return now;
    }
    return -1;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
