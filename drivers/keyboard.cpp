#include <hw/port_io.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <hw/isr.h>
#include <kmem.h>

static char keyBuffer[1024];
static int keyBufferPos = 0;


static void keyboardCallback(registers_t regs)
{
  UInt8 scancode = portByteIn(0x60);
  UInt8 scanmasked = (scancode & 0x7F); // if high bit is set, this is a key up event

  // if scancode outside of mapped range, ignore it
  if(scanmasked < 0 || scanmasked > 0x58)
  {
    return;
  }

  keyBuffer[keyBufferPos] = scancode;
  ++keyBufferPos;
  if(keyBufferPos >= 1024)
  {
    keyBufferPos = 1023;
    // FIXME: we should beep here!
  }
}

void initKeyboard()
{
  keyBufferPos = 0;
  registerInterruptHandler(IRQ1, keyboardCallback);
}

UInt16 getKeyboardBuffer(char *buffer, UInt16 bufferLen)
{
  UInt16 pos = keyBufferPos; // grab this because interrupts will change it
  // read either as much as the buffer will hold or as much as we have
  UInt16 len = ((bufferLen < pos) ? bufferLen : pos);

  if(buffer == 0)
  {
    return 0; // can't read into NULL buffer!
  }
  memcpy(buffer, keyBuffer, len);

  // now preserve what's left (if anything) in the input buffer and
  // reset the write pointer. Quickly, and with interrupts off, of course.
  asm("cli");
  memcpy(keyBuffer, &keyBuffer[pos], keyBufferPos - len);
  keyBufferPos = keyBufferPos - len;
  asm("sti");

  // return number of bytes stored in buffer
  return len;
}
