/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef PORTIO_H
#define PORTIO_H

#include <hw/types.h>

UInt8 portByteIn(UInt16 port);
void portByteOut(UInt16 port, UInt8 data);
UInt16 portWordIn(UInt16 port);
void portWordOut(UInt16 port, UInt16 data);
UInt32 portDWordIn(UInt16 port);
void portDWordOut(UInt16 port, UInt32 data);

#endif
