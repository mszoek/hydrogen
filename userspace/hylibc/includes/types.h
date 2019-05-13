/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#ifndef H2_TYPES_H
#define H2_TYPES_H

/* Integers */

typedef unsigned long long UInt64;
typedef unsigned       int UInt32;
typedef unsigned     short UInt16;
typedef unsigned      char UInt8;
typedef signed   long long SInt64;
typedef signed         int SInt32;
typedef signed       short SInt16;
typedef signed        char SInt8;

/*
	char, short, int, long, and long long should
	all be included by default during compilation.
	If not, FIXME: implement char, short, int, etc...
*/

/* Storage sizes */

#define KB 1024
#define MB (KB * 1024)
#define GB (MB * 1024)
#define TB (GB * 1024)
#define PB (TB * 1024)

/* C types */
//typedef UInt64 size_t;
//typedef UInt64 time_t; // TODO: Determine if time_t is actually a UInt64 or not...


#endif
