/*
 * H2 Kernel Scheduler
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/timer.h>
#include <sched.h>
#include <kstdio.h>

TaskControlBlock *curTask = 0;
TaskControlBlock *readyToRunStart = 0;
TaskControlBlock *readyToRunEnd = 0;

UInt32 schedulerSpinlock = 0;

/* FIXME: a real spinlock is needed for SMP */
void Scheduler::lock()
{
  asm("cli");
  ++schedulerSpinlock;
}

void Scheduler::unlock()
{
  --schedulerSpinlock;
  if(schedulerSpinlock == 0)
    asm("sti");
}

void Scheduler::updateTimeUsed(TaskControlBlock *task)
{
  UInt64 now = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  task->timeUsed += (now - task->lastTime) * 1000; // microseconds? I think.
  task->lastTime = now;
}

void Scheduler::blockTask(TaskState state)
{
  Scheduler::lock();
  curTask->state = state;
  Scheduler::schedule();
  Scheduler::unlock();
}

void Scheduler::unblockTask(TaskControlBlock *task)
{
  Scheduler::lock();
  if(readyToRunStart != 0)
  {
    // there is something on the run queue. append this task to the end.
    task->state = readyToRun;
    task->next = 0;
    readyToRunEnd->next = task;
    readyToRunEnd = task;
  } else {
    // there is only one currently running task. pre-empt it.
    switchTask(task);
  }
  Scheduler::unlock();
}

void Scheduler::schedule()
{
  if(readyToRunStart != 0)
  {
    TaskControlBlock *task = readyToRunStart;
    readyToRunStart = readyToRunStart->next;
    switchTask(task);
  }
}

TaskControlBlock *Scheduler::createTask(void (&entry)(), char *name)
{
  static UInt32 taskID = 2;

  TaskControlBlock *tcb = (TaskControlBlock *)vmm->malloc(sizeof(TaskControlBlock));
  tcb->tid = taskID++;
  tcb->sp = (UInt64)vmm->malloc(4096);
  tcb->usersp = 0;
  tcb->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  tcb->timeUsed = 0;
  tcb->state = readyToRun;
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
  tcb->next = 0;

  if(readyToRunStart == 0)
    readyToRunStart = tcb;
  if(readyToRunEnd == 0)
    readyToRunEnd = tcb;
  else
  {
    readyToRunEnd->next = tcb;
    readyToRunEnd = tcb;
  }
  return tcb;
}