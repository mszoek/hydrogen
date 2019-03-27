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
RootDisk rootDisk;

bool runMemTest = false;
bool verbose = false;

// Prototypes
void displayStatusLine();
void displayStartupMsg(unsigned int size);

// Kernel entry function
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size)
{
  UInt32 mem = 0;
  UInt32 mmap = 0, mmapLen = 0;
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
  }

  PhysicalMemoryManager physMM(mem, KERN_ADDRESS, size,
    (PhysicalMemoryManager::RegionInfo *)mmap, mmapLen);
  pmm = &physMM;

  char *s = 0;
  int index = 0;
  while((s = strtok(cmdline, " ", &index)) != 0)
  {
    // FIXME: parse the command line options to get root disk, verbosity, etc.
    if(strcmp(s, "verbose") == 0)
      verbose = true;
    else if(strncmp(s, "rd=", 3) == 0)
    {
      int x = 0;
      s = &s[3];
      while(s[x] != 0)
      {
        if(s[x] == '/')
        {
          s[x] = 0;
          rootDisk.bus = atoi(s);
          s = &s[x + 1];
          x = 0;
        } else if(s[x] == '.')
        {
          s[x] = 0;
          rootDisk.slot = atoi(s);
          s = &s[x + 1];
          x = 0;
        } else if(s[x] == ',')
        {
          s[x] = 0;
          rootDisk.func = atoi(s);
          s = &s[x + 1];
          rootDisk.part = atoi(s);
          break;
        }
        ++x;
      }
      kprintf("root disk: bus=%d slot=%d func=%d part=%d\n",rootDisk.bus,rootDisk.slot,rootDisk.func,rootDisk.part);
    }
  }

  isrInstall();
  TimerController *ctrlTimer = new TimerController();
  new KeyboardController();
  PCIController *ctrlPCI = new PCIController();
  ctrlPCI->pciEnumBuses();

  asm volatile("sti"); // Start interrupts!

  ctrlPCI->startDevices();

  kprint("\nStarting shell\n");
  shellStart();
  displayStatusLine();

  UInt32 blocks;
  UInt32 nrAllocs = 256;
  UInt32 pages[nrAllocs];
  int loops = nrAllocs;

  UInt16 diskbuf[512*1024]; // 512KB
  hbaPort *port = ((AHCIController *)g_controllers[CTRL_AHCI])->getPort(0);
  if(((AHCIController *)g_controllers[CTRL_AHCI])->read(port, diskbuf, 0, 1024))
  {
    kprint("\n");
    printdata((UInt8 *)diskbuf, 256);
  } else {
    kprint("Disk error\n");
  }

  while(1)
  {
      if(runMemTest && ctrlTimer->getTicks() % 1 == 0)
      {
        static int size = 8;
        if(loops == nrAllocs)
        {
          i = 0;
          memset((char*)pages, 0, sizeof(pages));
          blocks = pmm->memFreeBlocks();
          kprintf("Starting memory test. %d allocs. Free Blocks = %d\n", nrAllocs, blocks);
        }
        void *p = pmm->malloc(size);
        if(p != 0)
        {
          memset((char *)p, 0xC9, size);
          pages[i++] = (UInt32)p;
        } else {
          kprintf("malloc(%d) failed\n", size);
        }
        size *= 2;
        if(size > 3000) size = 8;
        if(size == 2048) size = 2032;
        --loops;
        if(loops == 0)
        {
          runMemTest = false;
          for(i = 0; i < nrAllocs; ++i)
            if(pages[i] != 0)
            {
              pmm->free((void*)pages[i]);
              pages[i] = 0;
            }
          kprintf("Finished memory test. Free blocks = %d, orig = %d\n", pmm->memFreeBlocks(), blocks);
          loops = nrAllocs;
        }
      }

      if(ctrlTimer->getTicks() % 500 == 0)
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
        kprintf("%8x ",i);
      kprintf("%2x ", nodedata[i]);
      ascii[j++] = isprint(nodedata[i]) ? nodedata[i] : '.';
      if(j > 15)
      {
        kprintf("%s\n",ascii);
        j=0;
      }
  }
}


void panic()
{
  kprintf("!PANIC! System halted.\n");
  asm("cli; hlt;");
}