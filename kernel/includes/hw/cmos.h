/*
 * H2 CMOS I/O Driver
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef CMOS_H
#define CMOS_H

UInt8 cmosRead(UInt8 reg);
void cmosWrite(UInt8 reg, UInt8 value);

#endif
