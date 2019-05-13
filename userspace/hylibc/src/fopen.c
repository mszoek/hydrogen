/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#include <string.h>

#ifndef __STDC_NO_THREADS__
#include <threads.h>
extern mtx_t _PDCLIB_filelist_mtx;
#endif

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

struct _PDCLIB_file_t * fopen( const char * _PDCLIB_restrict filename, const char * _PDCLIB_restrict mode )
{
    struct _PDCLIB_file_t * rc;
    size_t filename_len;
    if ( mode == NULL || filename == NULL || filename[0] == '\0' )
    {
        /* Mode or filename invalid */
        return NULL;
    }
    /* To reduce the number of malloc calls, all data fields are concatenated:
       * the FILE structure itself,
       * ungetc buffer,
       * filename buffer,
       * data buffer.
       Data buffer comes last because it might change in size ( setvbuf() ).
    */
    filename_len = strlen( filename ) + 1;
    /* See tmpfile(), which does much of the same. */
    if ( ( rc = calloc( 1, sizeof( struct _PDCLIB_file_t ) + _PDCLIB_UNGETCBUFSIZE + filename_len + BUFSIZ ) ) == NULL )
    {
        /* no memory */
        return NULL;
    }
    if ( ( rc->status = _PDCLIB_filemode( mode ) ) == 0 )
    {
        /* invalid mode */
        free( rc );
        return NULL;
    }
#ifndef __STDC_NO_THREADS__
    if ( mtx_init( &rc->mtx, mtx_plain | mtx_recursive ) != thrd_success )
    {
        /* could not initialize stream mutex */
        free( rc );
        return NULL;
    }
#endif
    rc->handle = _PDCLIB_open( filename, rc->status );
    if ( rc->handle == _PDCLIB_NOHANDLE )
    {
        /* OS open() failed */
#ifndef __STDC_NO_THREADS__
        mtx_destroy( &rc->mtx );
#endif
        free( rc );
        return NULL;
    }
    /* Setting pointers into the memory block allocated above */
    rc->ungetbuf = (unsigned char *)rc + sizeof( struct _PDCLIB_file_t );
    rc->filename = (char *)rc->ungetbuf + _PDCLIB_UNGETCBUFSIZE;
    rc->buffer   = rc->filename + filename_len;
    /* Copying filename to FILE structure */
    strcpy( rc->filename, filename );
    /* Initializing the rest of the structure */
    rc->bufsize = BUFSIZ;
    rc->bufidx = 0;
    rc->ungetidx = 0;
    /* Setting buffer to _IOLBF because "when opened, a stream is fully
       buffered if and only if it can be determined not to refer to an
       interactive device."
    */
    rc->status |= _IOLBF;
    /* TODO: Setting mbstate */
    /* Adding to list of open files */
    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
    return rc;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Some of the tests are not executed for regression tests, as the libc on
       my system is at once less forgiving (segfaults on mode NULL) and more
       forgiving (accepts undefined modes).
    */
    FILE * fh;
    remove( testfile );
    TESTCASE_NOREG( fopen( NULL, NULL ) == NULL );
    TESTCASE( fopen( NULL, "w" ) == NULL );
    TESTCASE_NOREG( fopen( "", NULL ) == NULL );
    TESTCASE( fopen( "", "w" ) == NULL );
    TESTCASE( fopen( "foo", "" ) == NULL );
    TESTCASE_NOREG( fopen( testfile, "wq" ) == NULL ); /* Undefined mode */
    TESTCASE_NOREG( fopen( testfile, "wr" ) == NULL ); /* Undefined mode */
    TESTCASE( ( fh = fopen( testfile, "w" ) ) != NULL );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
