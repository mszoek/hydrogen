/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/idt.h>
#include <hw/timer.h>
#include <hw/pci.h>
#include <hw/ata.h>
#include <hw/keyboard.h>
#include <hw/screen.h>
#include <kstring.h>
#include <kmem.h>
#include <kstdio.h>
#include <kversion.h>
#include <bootinfo.h>
#include <shell.h>

PhysicalMemoryManager *pmm = 0;
UInt32 g_controllers[CONTROLLER_MAX];

bool runMemTest = false;
bool verbose = true;

// Prototypes
void displayStatusLine();
void displayStartupMsg(unsigned int size);

// Kernel entry function
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size)
{
  UInt32 mem = 0;
  UInt32 mmap = 0, mmapLen = 0;
  UInt32 pages[16];
  int i = 0;
  char cmdline[256];
  
  memset(cmdline, 0, sizeof(cmdline));

  ScreenController screen;
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
    kprintf("; memory map loaded %d @ 0x%x\n", mmapLen, mmap);
  }
  if(binf->flags & 0x4)
  {
    strcpy(cmdline, (char *)(binf->cmdLine));

    // FIXME: parse the command line options to get root disk, verbosity, etc.
  }

  isrInstall();
  TimerController ctrlTimer;
  KeyboardController ctrlKbd;
  PhysicalMemoryManager physMM(mem, KERN_ADDRESS, size,
    (PhysicalMemoryManager::RegionInfo *)mmap, mmapLen);
  pmm = &physMM;
  pciEnumBuses();

  asm volatile("sti"); // Start interrupts!

  /* interrupts must be enabled for ATA init because we need the timer
     to create delays after I/O */
  for(int j = 0; j < 64; j++)
  {
    if(pciTable[j].bus == 0xFFFFFFFF)
      break;
    if(pciTable[j].classCode == PCI_MASS_STORAGE_CTRL)
    {
      switch(pciTable[j].subclassCode)
      {
        case 0x6:
          probeSATAPort((hbaMem *)(pciTable[j].baseAddrReg[5]));
          break;
        default:
          kprintf("Unsupported storage controller: 0x%x", pciTable[j].subclassCode);
      }
    }
  }

  kprint("\nStarting shell\n");
  shellStart();
  displayStatusLine();


  memset((char*)pages, 0, sizeof(pages));
  while(1)
  {
      if(runMemTest && ctrlTimer.getTicks() % 100 == 0)
      {
        if(pages[i] != 0)
        {
            pmm->free((void*)pages[i]);
        }
        void *p = pmm->alloc();
        if(p != 0)
        {
          memset((char *)p, i < 10 ? i+'0' : i-10+'A', PMM_BLOCK_SIZE);
          pages[i++] = (UInt32)p;
          if(i > 15)
          {
              i = 0;
          }
        } else {
          kprintAt("!PANIC! Out of memory!", -1, -1, 0x4f);
          return; // halt system
        }
        *((char *)p+1360) = 0;
        int pos = screen.getCursorOffset();
        screen.setCursorOffset(ScreenController::getOffset(0, 1));
        kprintf("Page %d 0x%x         ", i, (UInt32)p);
        kprintAt((char *)p, 0, 2, 0x03);
        screen.setCursorOffset(pos);
      }

      if(ctrlTimer.getTicks() % 500 == 0)
      {
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

  ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
  if(!screen)
    return;

  curpos = screen->getCursorOffset();

  memset(line, 0, sizeof(line));
  memcpy(line, "Mem Free: ", 10);
  itoa(pmm->memFreeBlocks(), 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  memcpy(line+strlen(line), " blocks Uptime: ", 16);
  itoa(((TimerController *)g_controllers[CTRL_TIMER])->getSeconds(), 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  i = strlen(line);
  line[i] = 's';
  line[i+1] = 0;
  memset(line+strlen(line), 0x20, sizeof(line)-strlen(line)-2); // space fill to right edge
  kprintAt(line, 0, 0, DEFAULT_STATUS_ATTR);

  screen->setCursorOffset(curpos);
}

void displayStartupMsg(unsigned int size)
{
  ScreenController *screen = ((ScreenController *)g_controllers[CTRL_SCREEN]);
  if(!screen)
    return;

  screen->defaultTextAttr(BG_BLACK | FG_GREY | FG_BOLD);
  screen->clearScreen();
  screen->setCursorOffset(ScreenController::getOffset(0, 2));
  kprintf("H2OS Kernel Started! v%d.%d.%d.%d [%d bytes @ 0x%x]\n", KERN_MAJOR, KERN_MINOR, KERN_SP, KERN_PATCH, size, KERN_ADDRESS);
  kprint("Copyright (C) 2017-2019 H2. All Rights Reserved!\n\n");
  screen->defaultTextAttr(DEFAULT_TEXT_ATTR);
}

char isprint (unsigned char c)
{
    if ( c >= 0x20 && c <= 0x7e )
        return 1;
    return 0;
}

void printdata(UInt8* nodedata, int len)
{
  char ascii[20];
  int i,j=0;

  for(i=0,j=0; i<len; ++i)
  {
      if(j==0)
        kprintf("%x ",i);
      kprintf("%x ", nodedata[i]);
      ascii[j++] = isprint(nodedata[i]) ? nodedata[i] : '.';
      if(j > 15)
      {
        kprintf("%s\n",ascii);
        j=0;
      }
  }
}
