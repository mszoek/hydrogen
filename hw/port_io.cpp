#include <hw/port_io.h>

// Read a byte from a specified port
UInt8 portByteIn(UInt16 port)
{
  UInt8 result;
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void portByteOut(UInt16 port, UInt8 data)
{
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

UInt16 portWordIn(UInt16 port)
{
  UInt16 result;
  asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void portWordOut(UInt16 port, UInt16 data)
{
  asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}

UInt32 portDWordIn(UInt16 port)
{
  UInt32 result;
  asm("in %%dx, %%eax" : "=a" (result) : "d" (port));
  return result;
}

void portDWordOut(UInt16 port, UInt32 data)
{
  asm("out %%eax, %%dx" : : "a" (data), "d" (port));
}
