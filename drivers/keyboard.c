#include <hw/port_io.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <hw/isr.h>
#include <kmem.h>

static char keyBuffer[1024];
static int keyBufferPos = 0;

// map scan codes 0x00 to 0x58 into en_US layout
const char scanCodesToASCII[] =
{
    -1, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x08,
    0x09, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x0D,
    -1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    -1, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

static void keyboardCallback(registers_t regs)
{
  int keyUp = 0;
  UInt8 scancode = portByteIn(0x60);

  if(scancode & 0x80) // if high bit set, this is a key up event
  {
    scancode &= 0x7F; // clear the high bit to get the real code
    keyUp = 1; // but remember it was set
  }

  // if scancode outside of mapped range, ignore it
  if(scancode < 0 || scancode > 0x58)
  {
    return;
  }

  // get the unshifted scancode in ASCII
  if(keyUp)
  {
    if(scancode == 0x1C)
    {
      kprint("\n");
      keyBuffer[keyBufferPos]=0;
      shellStart();
      return;
    }
    if (scancode == 0x0E)
    {
      keyBuffer[--keyBufferPos] = 0;
      printBackspace();
      return;
    }

    char ch = scanCodesToASCII[scancode];
    char key[2];
    key[0]=ch;
    key[1]=0;
    kprint(key);
    keyBuffer[keyBufferPos] = ch;
    ++keyBufferPos;
    if(keyBufferPos >= 1024)
    {
      keyBufferPos = 1023;
      // FIXME: we should beep here!
    }
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
