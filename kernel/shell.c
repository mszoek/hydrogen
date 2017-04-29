#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kmem.h>
#include <kstring.h>
#include <hw/types.h>

void shellStart()
{
  char charBuffer[1024];
  int length = getKeyboardBuffer(&charBuffer, 1023);

  if(length == 0)
  {
    return; // all they did was hit Enter
  }
  charBuffer[length] = '\0';

  if(strcmp(charBuffer, "exit") == 0)
  {
    kprint("kk, kthxbye!\n");
    asm("cli");
    asm("hlt");
  }
}
