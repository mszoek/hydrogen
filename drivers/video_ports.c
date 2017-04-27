#include <drivers/video_ports.h>

// Read a byte from a specified port
unsigned char portByteIn (unsigned short port)
{
  unsigned char result;
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void portByteOut (unsigned short port, unsigned char data)
{
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short portWordIn (unsigned short port)
{
  unsigned short result;
  asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void portWordOut (unsigned short port, unsigned short data)
{
  asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
