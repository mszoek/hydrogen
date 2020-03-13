/*
 * H2 CMOS I/O Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/types.h>
#include <hw/port_io.h>

#define CMOS_SEL 0x70
#define CMOS_DATA 0x71
#define NMI_DISABLE 0

UInt8 cmosRead(UInt8 reg)
{
    portByteOut(CMOS_SEL, (NMI_DISABLE << 7) | reg);
    asm volatile("mov $0xFFFF, %ecx; x0: loop x0");
    UInt8 value = portByteIn(CMOS_DATA);
    return value;
}

void cmosWrite(UInt8 reg, UInt8 value)
{
    portByteOut(CMOS_SEL, (NMI_DISABLE << 7) | reg);
    asm volatile("mov $0xFFFF, %ecx; x1: loop x1");
    portByteOut(CMOS_DATA, value);
}
