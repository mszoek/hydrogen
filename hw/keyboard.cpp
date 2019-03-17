#include <kernel.h>
#include <hw/port_io.h>
#include <hw/keyboard.h>
#include <hw/screen.h>
#include <hw/isr.h>
#include <kmem.h>


static void keyboardCallback(registers_t regs)
{
  UInt8 scancode = portByteIn(0x60);
  UInt8 scanmasked = (scancode & 0x7F); // if high bit is set, this is a key up event

  // if scancode outside of mapped range, ignore it
  // if no handler object for this IRQ, ignore it
  if(scanmasked < 0 || scanmasked > 0x58 || !g_controllers[CTRL_KEYBOARD])
    return;

  ((KeyboardController *)g_controllers[CTRL_KEYBOARD])->insertBuffer(scancode);
}

KeyboardController::KeyboardController()
{
  if(verbose)
    kprintf("hw/KeyboardController: 0x%x\n", this);
  keyBufferPos = 0;
  g_controllers[CTRL_KEYBOARD] = (UInt32)this; // assume ownership of keyboard input
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
