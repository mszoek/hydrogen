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

#define DEFAULT_TEXT_ATTR 0x07    // grey on black
#define DEFAULT_STATUS_ATTR 0x5e  // yellow on magenta

extern UInt32 tickCounter; // in timer.c

// Prototypes
void displayStatusLine();
void displayStartupMsg(unsigned int size);

// Kernel entry function
void kernelMain(struct multiboot_info *binf, unsigned int size)
{
  char buf[10];
  UInt32 mem = 0;
  UInt32 mmap = 0, mmapLen = 0;
  
  displayStartupMsg(size);

  /* Read data from the multiboot structure */
  if(binf->flags & 0x1)
  {
    mem = binf->memHi + binf->memLo + 1024;
    itoa(mem, buf);
    kprint(buf);
    kprint(" KB memory");
  }
  if(binf->flags & 0x40) 
  {
    mmap = binf->mmapAddr;
    mmapLen = binf->mmapLen;
    itoa(binf->mmapAddr, buf);
    kprint("; memory map loaded");
  }

  kprint("\n\nisrInstall()\n");
  isrInstall();
  kprint("initKeyboard()\n");
  initKeyboard();
  kprint("initTimer()\n");
  initTimer(100);

  /* Start the memory manager */
  kprint("pmmInit()\n");
  pmmInit(mem, 0x1000000, size, mmap, mmapLen);

  displayStatusLine();

  asm volatile("sti"); // Start interrupts!

  while(1)
  {
      if(tickCounter % 100 == 0) displayStatusLine();
      asm("hlt"); // sleep until next interrupt
  }
}

void displayStatusLine()
{
  int curpos;
  char attr;
  char s[25], line[81];

  curpos = getCursorOffset();

  memset(line, 0, sizeof(line));
  memcpy(line, "Mem Free: ", 10);
  itoa(pmmMemFreeBlocks(), s);
  memcpy(line+strlen(line), s, strlen(s));
  memcpy(line+strlen(line), " blocks Uptime: ", 16);
  itoa(tickCounter, s);
  memcpy(line+strlen(line), s, strlen(s));
  memset(line+strlen(line), 0x20, sizeof(line)-strlen(line)-2); // space fill to right edge
  kprintAt(line, 0, 24, DEFAULT_STATUS_ATTR);

  setCursorOffset(curpos);
}

void displayStartupMsg(unsigned int size)
{
  char msgStartup[] = "H2OS Kernel Started! v";
  clearScreen(DEFAULT_TEXT_ATTR);
  defaultTextAttr(DEFAULT_TEXT_ATTR);
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
