#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <hw/types.h>
#include <hw/isr.h>


void initKeyboard();
UInt16 getKeyboardBuffer(char *buffer, UInt16 bufferLen);
static void keyboardCallback(registers_t regs);

#endif
