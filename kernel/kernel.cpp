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
#include <kstdio.h>
#include <kversion.h>
#include <shell.h>
#include <hw/byteswap.h>

#define KERNEL_HFS
#include <fs/hfs.h>

// some global stuff
PhysicalMemoryManager *pmm = 0;
VirtualMemoryManager *vmm = 0;
UInt64 g_controllers[CONTROLLER_MAX];
StorageList *g_storage = 0;
char rootGUID[40]; // root filesystem GUID from cmdline
Partition *rootPartition = 0;
struct multiboot_info bootinfo;

bool verbose = false;
bool debug = false;

// Prototypes
void displayStatusLine();
void displayStartupMsg(unsigned int size);

// Kernel entry function
extern "C" void kernelMain(struct multiboot_info *binf, unsigned int size)
{
  UInt64 mem = 0, mmap = 0, mmapLen = 0;
  int i = 0;
  char cmdline[256];
  
  memset(cmdline, 0, sizeof(cmdline));
  memset(rootGUID, 0, sizeof(rootGUID));
  memcpy((char *)&bootinfo, (char *)binf, sizeof(bootinfo));


  /* Read data from the multiboot structure */
  if(binf->flags & 0x1)
    mem = binf->memHi + binf->memLo + 1024;
  if(binf->flags & 0x40) 
  {
    mmap = binf->mmapAddr;
    mmapLen = binf->mmapLen;
  }
  if(binf->flags & 0x4)
    strcpy(cmdline, (char *)((UInt64)binf->cmdLine));

  PhysicalMemoryManager physMM(mem, KERN_ADDRESS, size,
    (PhysicalMemoryManager::RegionInfo *)mmap, mmapLen);
  pmm = &physMM;

  VirtualMemoryManager virtMM;
  vmm = &virtMM;

  new ScreenController();
  ScreenController *screen = ((ScreenController *)g_controllers[CTRL_SCREEN]);
  if(!screen)
    panic();

  char *s = 0;
  int index = 0;
  while((s = strtok(cmdline, " ", &index)) != 0)
  {
    if(strcmp(s, "verbose") == 0)
      verbose = true;
    if(strcmp(s, "debug") == 0)
      debug = true;
    else if(strncmp(s, "rd=", 3) == 0)
      strcpy(rootGUID, &s[3]);
    else if(strncmp(s, "font=", 5) == 0)
      screen->setFont(atoi(&s[5]));
  }

  screen->clearScreen();
  screen->drawLogo();
  screen->setColor(0xE0E0F0);
  kprintf("H2OS Kernel Started! v%d.%d.%d.%d [%d bytes @ 0x%x]\n", KERN_MAJOR, KERN_MINOR, KERN_SP, KERN_PATCH, size, KERN_ADDRESS);
  kprint("Copyright (C) 2017-2019 H2. All Rights Reserved!\n\n");
  screen->setColor(0xB0B0B0);
  isrInstall();

  TimerController *ctrlTimer = new TimerController();
  new KeyboardController();
  PCIController *ctrlPCI = new PCIController();
  ctrlPCI->pciEnumBuses();
  asm volatile("sti"); // Start interrupts!
  ctrlPCI->startDevices();

  // look for partition tables if we found some disks.
  // enumerate them all so they get displayed, even if no root UUID to mount
  for(StorageList *iter = g_storage; iter != 0; iter = iter->next)
  {
    GUIDPartitionTable *gpt = 0;
    
    if(iter->controllerType == CTRL_AHCI)
      gpt = new GUIDPartitionTable((AHCIController *)iter->controller, iter->port);

    if(rootGUID[0] != 0 && gpt->isValid())
    {
      rootPartition = new Partition(*gpt->getPartitionByGUID(rootGUID));
      free(gpt);

      kprintf("Mounting %s root partition %s\n",
          (rootPartition->getTypeEntry())->name, rootPartition->getGUIDA());
      HierarchicalFileSystem *hfs = new HierarchicalFileSystem(rootPartition);
    }
  }

  shellStart();
  displayStatusLine();

  while(1)
  {
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
  char s[25], line[81];

  ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
  if(!screen)
    return;

  UInt32 x = screen->getX();
  UInt32 y = screen->getY();
  UInt32 bg = screen->getBackColor();

  memset(line, 0, sizeof(line));
  memcpy(line, "Mem Free: ", 10);
  itoa(pmm->memFreeBlocks(), 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  memcpy(line+strlen(line), " blocks Uptime: ", 16);
  itoa(((TimerController *)g_controllers[CTRL_TIMER])->getSeconds(), 10, s);
  memcpy(line+strlen(line), s, strlen(s));
  int i = strlen(line);
  line[i] = 's';
  line[i+1] = 0;
  memset(line+strlen(line), 0x20, sizeof(line)-strlen(line)-2); // space fill to right edge
  screen->setXY(0, 0);
  screen->setBackColor(0x00277c);
  kprint(line);
  screen->setXY(x, y);
  screen->setBackColor(bg);
}

void panic()
{
  asm("cli");
  kprintf("PANIC! at the disco. System halted.\n");
  // FIXME: dump registers and stack here
  asm("hlt");
}