#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <hw/types.h>

static inline UInt16 bswap16(UInt16 v)
{
    asm volatile("xchgb %b0, %h0" : "=q"(v) : "0"(v));
    return v;
}
static inline UInt32 bswap32(UInt32 v)
{
    asm volatile("bswap %0" : "=q"(v) : "0"(v));
    return v;
}

static inline UInt64 bswap64(UInt64 v)
{
    asm volatile("bswap %0" : "=q"(v) : "0"(v));
    return v;
}

#endif // BYTESWAP_H
