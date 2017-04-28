#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kmem.h>
#include <kstring.h>
#include <hw/types.h>

void shellStart()
{
  kprint("H2OS CodeGrlz Shell\n");
  char charBuffer[1024];
  int length = getKeyboardBuffer(charBuffer, 1024);
  charBuffer[length-1] = '\0';
  kprint(charBuffer);

  if (strcmp(charBuffer, "exit") == 0)
  {
    asm volatile ("hlt");
  }
}
