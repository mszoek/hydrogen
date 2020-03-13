/*
 * H2 Keyboard Input Controller
 * Copyright (C) 2019 Zoe Knox. All rights reserved.
 */
#include <kernel.h>
#include <hw/port_io.h>
#include <hw/keyboard.h>
#include <hw/screen.h>
#include <hw/isr.h>
#include <kmem.h>
#include <kstdio.h>
#include <sched.h>

// map scan codes 0x00 to 0x58 into en_US layout
const char KeyboardController::scanCodesToASCII_base[] =
{
    -1, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x08,
    0x09, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x0A,
    -1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    -1, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

const char KeyboardController::scanCodesToASCII_shift[] =
{
    -1, 0x1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0x08,
    0x09, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0x0A,
    -1, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
    -1, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

static void keyboardCallback(registers_t regs)
{
  UInt8 scancode = portByteIn(0x60);
  UInt8 scanmasked = (scancode & 0x7F); // if high bit is set, this is a key up event

  // if scancode outside of mapped range, ignore it
  // if no handler object for this IRQ, ignore it
  if(scanmasked < 0 || scanmasked > 0x58 || !g_controllers[CTRL_KEYBOARD])
    return;

  ((KeyboardController *)g_controllers[CTRL_KEYBOARD])->insertBuffer(scancode);

  TaskControlBlock *task = waitQ;
  waitQ = 0;

  while(task != 0)
  {
    TaskControlBlock *cur = task;
    task = task->next;

    if(cur->state == waitIO)
    {
      cur->next = 0;
      Scheduler::unblockTask(cur);
    } else {
      cur->next = waitQ;
      waitQ = cur;
    }
  }

  // need to preempt curTask?
  if(curTask != 0)
  {
    if(curTask->timeSlice <= 1)
      Scheduler::schedule();
    else
      curTask->timeSlice -= 1;
  }
}

KeyboardController::KeyboardController()
{
  if(verbose)
    kprintf("hw/KeyboardController: 0x%x\n", this);
  keyBufferPos = 0;
  g_controllers[CTRL_KEYBOARD] = (UInt64)this; // assume ownership of keyboard input
  registerInterruptHandler(IRQ1, keyboardCallback);
}

KeyboardController::~KeyboardController()
{
  g_controllers[CTRL_KEYBOARD] = 0;
  registerInterruptHandler(IRQ1, 0);
}

UInt16 KeyboardController::insertBuffer(UInt8 scancode)
{
  keyBuffer[keyBufferPos] = scancode;
  ++keyBufferPos;
  if(keyBufferPos >= 1024)
  {
    keyBufferPos = 1023;
    // FIXME: we should beep here!
  }
  return keyBufferPos;
}

UInt16 KeyboardController::getKeyboardBuffer(UInt8 *buffer, UInt16 bufferLen)
{
  UInt16 pos = keyBufferPos; // grab this because interrupts will change it
  // read either as much as the buffer will hold or as much as we have
  UInt16 len = ((bufferLen < pos) ? bufferLen : pos);

  if(buffer == 0)
  {
    return 0; // can't read into NULL buffer!
  }
  memcpy((char *)buffer, keyBuffer, len);

  // now preserve what's left (if anything) in the input buffer and
  // reset the write pointer. Quickly, and with interrupts off, of course.
  asm("cli");
  memcpy((char *)keyBuffer, (char *)&keyBuffer[pos], keyBufferPos - len);
  keyBufferPos = keyBufferPos - len;
  asm("sti");

  // return number of bytes stored in buffer
  return len;
}

int KeyboardController::translateCodes(UInt8 *buffer, UInt16 bufferLen)
{
  bool shifted = false;
  int j = 0;

  for(int i = 0; i < bufferLen; ++i)
  {
    bool keyUp = false;
    char code = buffer[i];

    if(code == 0xE1 || code == 0x2A)
    {
      shifted = true;
      continue;
    }
    else if(((code & 0x7F) == 0x2A))
    {
      shifted = false;
      continue;
    }

    if(code & 0x80)
    {
      keyUp = true;
      code &= 0x7F;
    }

    if(!keyUp)
    {
      code = shifted ? scanCodesToASCII_shift[code] : scanCodesToASCII_base[code];
      if(code >= 0)
        buffer[j++] = code;
    }
  }

  return j; // return number of characters after translation
}
