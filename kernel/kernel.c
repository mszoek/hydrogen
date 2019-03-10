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
  UInt32 mem = 0;
  UInt32 mmap = 0, mmapLen = 0;
  UInt32 pages[16];
  int i = 0;
  
  displayStartupMsg(size);

  /* Read data from the multiboot structure */
  if(binf->flags & 0x1)
  {
    mem = binf->memHi + binf->memLo + 1024;
    kprintf("%d KB memory", mem);
  }
  if(binf->flags & 0x40) 
  {
    mmap = binf->mmapAddr;
    mmapLen = binf->mmapLen;
    kprintf("; memory map loaded @ 0x%x", mmap);
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

  kprint("Starting shell\n");
  shellStart();
  displayStatusLine();

  asm volatile("sti"); // Start interrupts!

  memset(pages, 0, sizeof(pages));
  while(1)
  {
      if(tickCounter % 100 == 0)
      {
          if(pages[i] != 0)
          {
              pmmFree(pages[i]);
          }
          void *p = pmmAlloc();
          if(p != 0)
          {
              memset(p, i < 10 ? i+'0' : i-10+'A', PMM_BLOCK_SIZE);
              pages[i++] = p;
              if(i > 15)
              {
                  i = 0;
              }
          }
          // *((char *)p+1840) = 0;
          // kprintAt((char *)p, 0, 0, 0x03);
          displayStatusLine();
      }

      shellCheckInput();

      asm("hlt"); // sleep until next interrupt
  }
}

void displayStatusLine()
{
  int curpos, i;
  char attr;
  char s[25], line[81];

  curpos = getCursorOffset();

  memset(line, 0, sizeof(line));
  memcpy(line, "Mem Free: ", 10);
  itoa(pmmMemFreeBlocks(), 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  memcpy(line+strlen(line), " blocks Uptime: ", 16);
  itoa(tickCounter/100, 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  i = strlen(line);
  line[i] = 's';
  line[i+1] = 0;
  memset(line+strlen(line), 0x20, sizeof(line)-strlen(line)-2); // space fill to right edge
  kprintAt(line, 0, 0, DEFAULT_STATUS_ATTR);

  setCursorOffset(curpos);
}

void displayStartupMsg(unsigned int size)
{
  clearScreen(DEFAULT_TEXT_ATTR);
  defaultTextAttr(0x0f);
  setCursorOffset(getOffset(0, 2));
  kprintf("H2OS Kernel Started! v%d.%d.%d.%d [%d bytes @ 0x1000000]\n", KERN_MAJOR, KERN_MINOR, KERN_SP, KERN_PATCH, size);
  kprint("Copyright (C) 2017-2019 H2. All Rights Reserved!\n\n");
  defaultTextAttr(DEFAULT_TEXT_ATTR);
}
