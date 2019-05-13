/* _PDCLIB_errno

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_int.h"

static int _PDCLIB_errno = 0;

int * _PDCLIB_errno_func()
{
    return &_PDCLIB_errno;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <errno.h>

int main( void )
{
    errno = 0;
    TESTCASE( errno == 0 );
    errno = EDOM;
    TESTCASE( errno == EDOM );
    errno = ERANGE;
    TESTCASE( errno == ERANGE );
    return TEST_RESULTS;
}

#endif
