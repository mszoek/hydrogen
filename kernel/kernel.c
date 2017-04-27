// H2OS Kernel! CodeGrlz rule.

#include <hw/isr.h>
#include <hw/idt.h>
#include <hw/timer.h>
#include <drivers/keyboard.h>
#include <drivers/video_ports.h>
#include <drivers/screen.h>
#include <kstring.h>
#include <kmem.h>
#include <kversion.h>

void kernelMain(void)
{
  UInt8 major, minor, patch;
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
  kprint(".");
  itoa(KERN_PATCH, msgStartup);
  kprint(msgStartup);
  kprint("\nCopyright (C) 2017 CodeGrlz. All Rights Reserved!\n\n");

  kprint("isrInstall()\n");
  isrInstall();
  kprint("initTimer()\n");
  initTimer(1000);

  while(1) ;
}

void _start(void) {
  kernelMain();
}
