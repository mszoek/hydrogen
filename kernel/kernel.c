// H2OS Kernel! CodeGrlz rule.

#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/idt.h>
#include <hw/timer.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kstring.h>
#include <kmem.h>
#include <kversion.h>

void kernelMain(void)
{
  char msgStartup[] = "H2OS Kernel Started! v";
  clearScreen();
  kprint(msgStartup);
  itoa(KERN_MAJOR, msgStartup);
  kprint(msgStartup);
  kprint(".");
  itoa(KERN_MINOR, msgStartup);
  kprint(msgStartup);
  kprint(".");
  itoa(KERN_SP, msgStartup);
  kprint(msgStartup);
  kprint("p");
  itoa(KERN_PATCH, msgStartup);
  kprint(msgStartup);
  kprint("\nCopyright (C) 2017 CodeGrlz. All Rights Reserved!\n\n");

  kprint("isrInstall()\n");
  isrInstall();

  kprint("initKeyboard()\n");
  initKeyboard();
  kprint("initTimer()\n");
  initTimer(50);

  asm volatile("sti"); // Start interrupts!

  while(1) ;
}

