/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */


#include <hw/types.h>
#include <hw/keyboard.h>
#include <hw/screen.h>
#include <hw/pci.h>
#include <hw/ata.h>
#include <kstdio.h>
#include <kmem.h>
#include <kstring.h>
#include <kernel.h>
#include <shell.h>
#include <sched.h>

// map scan codes 0x00 to 0x58 into en_US layout
const char scanCodesToASCII_base[] =
{
    -1, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x08,
    0x09, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x0D,
    -1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    -1, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

const char scanCodesToASCII_shift[] =
{
    -1, 0x1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0x08,
    0x09, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0x0D,
    -1, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
    -1, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', -1, '*',
    -1, ' ', -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* f1 to f10 keys */
    -1, -1, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0',
    '.', -1, -1, -1, -1, -1
};

int shifted = 0;


char *PROMPT = "H2> ";
char shellBuffer[1024];
unsigned int shellBufferPos = 0;

void shellStart()
{
  memset(shellBuffer, 0, sizeof(shellBuffer));
  shellBufferPos = 0;
  kprint(PROMPT);
}

void shellExecCommand()
{
  ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];

  if(strlen(shellBuffer) < 1) return;

  if(strcmp(shellBuffer, "help") == 0)
  {
    kprintf("Commands:\n"
    "  break - invoke breakpoint\n  clear - clear the screen\n  lspci - list pci devices\n"
    "  printdata ADDR - print memory contents\n  meminfo - show memory pool info\n"
    "  ps - show kernel tasks\n\n");
    return;
  }

  if(strcmp(shellBuffer, "clear") == 0)
  {
    if(screen)
    {
      screen->clearScreen();
    }
    return;
  }

  if(strcmp(shellBuffer, "lspci") == 0)
  {
    PCIController *pci = (PCIController *)g_controllers[CTRL_PCI];
    if(!pci) return;

    bool temp = verbose;
    verbose = true;
    pci->pciEnumBuses();
    verbose = temp;
    return;
  }

  if(strncmp(shellBuffer, "printdata", 9) == 0)
  {
    UInt64 index = 0;
    char *p = strtok(shellBuffer, " ", (int *)&index);
    p = strtok(shellBuffer, " ", (int *)&index);
    if(p != 0)
      index = atoi16(p);
    else
      index = KERNEL_VMA;
    printdata((UInt8 *)index, 256);
    return;
  }

  if(strcmp(shellBuffer, "meminfo") == 0)
  {
    pmm->printStats();
    return;
  }

  if(strcmp(shellBuffer, "break") == 0)
  {
    asm volatile("int3");
    return;
  }

  if(strcmp(shellBuffer, "ps") == 0)
  {
    asm("cli");
    kprintf(" TID        TIME       STACK       STATE  NAME\n");
    kprintf("%6d  %9dus  %9x       %d      %s\n", curTask->tid, curTask->timeUsed/1000,
      curTask->sp, curTask->state, curTask->name);
    for(TaskControlBlock *tcb = runQ; tcb; tcb = tcb->next)
    {
      kprintf("%6d  %9dus  %9x       %d      %s\n", tcb->tid, tcb->timeUsed/1000,
        tcb->sp, tcb->state, tcb->name);
      if(tcb == runQEnd) break;
    }
    for(TaskControlBlock *tcb = sleepQ; tcb != 0; tcb = tcb->next)
    {
      kprintf("%6d  %9dus  %9x       %d      %s\n", tcb->tid, tcb->timeUsed/1000,
        tcb->sp, tcb->state, tcb->name);
    }
    asm("sti");
    return;
  }

  kprint("Invalid command\n");
}

void shellCheckInput()
{
  char code;
  int keyUp = 0;
  UInt8 buf[1024];
  int length = ((KeyboardController *)g_controllers[CTRL_KEYBOARD])->getKeyboardBuffer(buf, 1023);

  for(int i = 0; i < length; ++i)
  {
    char code = buf[i];

    if(code == 0xe1 || code == 0x2a)
    {
      shifted = 1;
      continue;
    }
    else if(((code & 0x7F) == 0x2A))
    {
      shifted = 0;
      continue;
    }

    if(code & 0x80)
    {
      keyUp = 1;
      code &= 0x7F;
    }

    if(!keyUp)
    {
      if(code == 0x1C)
      {
        kprintf("\n");
        shellBuffer[shellBufferPos++] = 0;
        shellExecCommand();
        shellBufferPos = 0;
        shellBuffer[0] = 0;
        kprintf(PROMPT);
        return;
      }
      if(code == 0x0E)
      {
        if(shellBufferPos > 0)
        {
          shellBuffer[--shellBufferPos] = 0;
          ScreenController *screen = (ScreenController *)g_controllers[CTRL_SCREEN];
          if(screen)
            screen->printBackspace();
        }
        return;
      }

      if(shellBufferPos >= 1023)
      {
        return;
        // FIXME: we should beep here
      }

      code = shifted ? scanCodesToASCII_shift[code] : scanCodesToASCII_base[code];
      shellBuffer[shellBufferPos++] = code;
      char key[2];
      key[0]=code;
      key[1]=0;
      kprintf(key);
    }
  }
}
