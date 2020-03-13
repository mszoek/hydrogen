/*
 * H2 Keyboard Input Controller
 * Copyright (C) 2019 Zoe Knox. All rights reserved.
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <hw/types.h>
#include <hw/isr.h>

static void keyboardCallback(registers_t regs);

class KeyboardController
{
public:
    KeyboardController();
    virtual ~KeyboardController();

    UInt16 getKeyboardBuffer(UInt8 *buffer, UInt16 bufferLen);
    int translateCodes(UInt8 *buffer, UInt16 bufferLen);
    UInt16 insertBuffer(UInt8 scancode);

private:
    char keyBuffer[1024];
    int keyBufferPos;

    static const char scanCodesToASCII_base[];
    static const char scanCodesToASCII_shift[];
};

#endif
