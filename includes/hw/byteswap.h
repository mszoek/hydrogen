#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <hw/types.h>

static inline UInt16 bswap16(UInt16 v)
{
    asm("xchgb %b0, %h0" : "=q"(v) : "0"(v));
    return v;
}
static inline UInt32 bswap32(UInt32 v)
{
    asm("bswap %0" : "=q"(v) : "0"(v));
    return v;
}

#endif // BYTESWAP_H