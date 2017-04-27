#ifndef HWTYPES_H
#define HWTYPES_H

// Define size-based types for arbitrary data. HFS+ uses the UInt* format

typedef unsigned long long UInt64;
typedef signed long long SInt64;
typedef unsigned int UInt32;
typedef signed int SInt32;
typedef unsigned short UInt16;
typedef signed short SInt16;
typedef unsigned char UInt8;
typedef signed char SInt8;

#define low16(address) (UInt16)((address) & 0xFFFF)
#define high16(address) (UInt16)(((address) >> 16) & 0xFFFF)

#endif
