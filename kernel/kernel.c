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
#include <bootinfo.h>

// Prototypes
void displayStartupMsg();

// Kernel entry function
void kernelMain(struct multiboot_info *binf, unsigned int size)
{
  char buf[10];
  unsigned int m = 0;

  displayStartupMsg(size);

  /* Read data from the multiboot structure */
  if(binf->flags & 0x1)
  {
    m = binf->memHi + binf->memLo + 1024;
    itoa(m, buf);
    kprint(buf);
    kprint(" KB memory\n");
  }
  if(binf->flags & 0x20)
  {
    itoa(binf->mmapAddr, buf);
    kprint("Map @ ");
    kprint(buf);
    kprint(", Len ");
    itoa(binf->mmapLen, buf);
    kprint(buf);
    kprint("\n");
  }

  kprint("\nisrInstall()\n");
  isrInstall();
  kprint("initKeyboard()\n");
  initKeyboard();
  kprint("initTimer()\n");
  initTimer(100);

  /* Start the memory manager */
  kprint("pmmInit()\n");
  pmmInit(m, 0x1000000 + size);

  asm volatile("sti"); // Start interrupts!

  while(1) ;
}

void displayStartupMsg(unsigned int size)
{
  char msgStartup[] = "H2OS Kernel Started! v";
  clearScreen(0x1f);
  defaultTextAttr(0x1f);
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
  kprint(" [");
  itoa(size, msgStartup);
  kprint(msgStartup);
  kprint(" bytes @ 0x1000000]\nCopyright (C) 2017-2019 H2. All Rights Reserved!\n\n");
}
