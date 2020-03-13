/* _PDCLIB_exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>
#include <syscall.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

void _PDCLIB_Exit( int status )
{
    _syscall( SYSCALL_EXIT, status, 0, 0, 0, 0 );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
#ifndef REGTEST
    int UNEXPECTED_RETURN = 0;
    _PDCLIB_Exit( 0 );
    TESTCASE( UNEXPECTED_RETURN );
#endif
    return TEST_RESULTS;
}

#endif
