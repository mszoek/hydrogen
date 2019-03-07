// Kernel timer interrupt
// Zoe Knox 2017

#include <hw/types.h>
#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/timer.h>
#include <kstring.h>
#include <drivers/screen.h>

UInt32 tickCounter = 0;

static void timerCallback(registers_t regs)
{
  tickCounter++;

  // every 50 ticks (~every second) print the current count
  // in the bottom right, and restore the previous cursor pos
  if(tickCounter % 50 == 0)
  {
    int pos = getCursorOffset();
    kprintAt("Uptime: ", 60, 24, 0x1e);
    char s[32];
    itoa(tickCounter, s);
    kprintAt(s, -1, -1, 0x1e);
    setCursorOffset(pos);
  }
}

void initTimer(UInt32 Hz)
{
  registerInterruptHandler(IRQ0, timerCallback);

  // Program the PIT! H/w clock is 1193180Hz, which is probably wrong
  UInt32 divisor = 1193180 / Hz;
  UInt8 low = (UInt8)(divisor & 0xFF);
  UInt8 high = (UInt8)((divisor >> 8) & 0xFF);
  portByteOut(0x43, 0x36);
  portByteOut(0x40, low);
  portByteOut(0x40, high);
}
