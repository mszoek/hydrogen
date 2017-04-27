// Kernel timer interrupt
// Zoe Knox 2017

#include <hw/types.h>
#include <hw/isr.h>
#include <hw/timer.h>
#include <kstring.h>
#include <drivers/screen.h>

UInt32 tickCounter = 0;

static void timerCallback(registers_t regs)
{
  char strTick[256];

  tickCounter++;
  itoa(tickCounter, strTick);
  kprint("TICK! ");
  kprint(strTick);
  kprint("\n");
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
