/*
 * H2 Timer Controller
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#include <hw/types.h>
#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/screen.h>
#include <hw/timer.h>
#include <kernel.h>
#include <kstdio.h>
#include <sched.h>

static void timerCallback(registers_t regs)
{
  if(g_controllers[CTRL_TIMER])
    ((TimerController *)g_controllers[CTRL_TIMER])->tick();
}

TimerController::TimerController()
{
  if(verbose)
    kprintf("hw/TimerController: 0x%x @%dHz\n", this, KERNEL_HZ);
  g_controllers[CTRL_TIMER] = (UInt64)this;

  tickCounter = 0;
  registerInterruptHandler(IRQ0, timerCallback);

  // Program the PIT! H/w clock is 1193180Hz
  UInt32 divisor = 1193180 / KERNEL_HZ;
  UInt8 low = (UInt8)(divisor & 0xFF);
  UInt8 high = (UInt8)((divisor >> 8) & 0xFF);
  portByteOut(0x43, 0x36);
  portByteOut(0x40, low);
  portByteOut(0x40, high);
}

TimerController::~TimerController()
{
  registerInterruptHandler(IRQ0, 0);
  g_controllers[CTRL_TIMER] = 0;
}

UInt64 TimerController::getTicks()
{
  return tickCounter;
}

UInt64 TimerController::getSeconds()
{
  return tickCounter / KERNEL_HZ;
}

void TimerController::tick()
{
  ++tickCounter;
  TaskControlBlock *task = sleepQ;
  sleepQ = 0;

  while(task != 0)
  {
    TaskControlBlock *cur = task;
    task = task->next;

    if(cur->wakeTime <= NANOTICKS*tickCounter)
    {
      cur->wakeTime = 0;
      cur->next = 0;
      Scheduler::unblockTask(cur);
    } else {
      cur->next = sleepQ;
      sleepQ = cur;
    }    
  }
}
