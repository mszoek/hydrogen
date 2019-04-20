/*
 * H2 Kernel Scheduler
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/timer.h>
#include <sched.h>
#include <kstdio.h>

TaskControlBlock *rootTask = 0;
TaskControlBlock *curTask = 0;

void Scheduler::updateTimeUsed(TaskControlBlock *task)
{
  UInt64 now = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  task->timeUsed += (now - task->lastTime) * 1000; // microseconds? I think.
  task->lastTime = now;
}

void Scheduler::schedule()
{
  updateTimeUsed(curTask);
  switchTask(curTask->next);
}

TaskControlBlock *Scheduler::createTask(void (&entry)(), char *name = 0)
{
  static UInt32 taskID = 2;

  TaskControlBlock *tcb = (TaskControlBlock *)vmm->malloc(sizeof(TaskControlBlock));
  tcb->tid = taskID++;
  tcb->next = rootTask->next;
  tcb->sp = vmm->malloc(4096);
  tcb->usersp = 0;
  tcb->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  tcb->timeUsed = 0;
  tcb->state = 0;
  if(name)
    strcpy(tcb->name, name);
  else
  {
    tcb->name[0] = '-';
    tcb->name[1] = 0;
  }
  asm(
    "mov %%rsp, %%r10;"
    "mov %2, %%rsp;"
    "push %1;" // return address
    "mov %%cr3, %%rbx;"
    "mov %%rbx, %0;"
    "mov %%r10, %%rsp"
    : "=m"(tcb->vas)
    : "r"(entry), "m"(tcb->sp)
  );
  tcb->sp -= 80;
  rootTask->next = tcb;
  return tcb;
}