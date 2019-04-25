/*
 * H2 Kernel Scheduler
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/timer.h>
#include <sched.h>
#include <kstdio.h>

TaskControlBlock *curTask = 0;
TaskControlBlock *runQ = 0;
TaskControlBlock *runQEnd = 0;
TaskControlBlock *sleepQ = 0;

UInt32 schedulerSpinlock = 0;
UInt32 locksHeld = 0;
bool taskSwitchDeferred = false;


void nanosleepUntil(UInt64 when)
{
  TimerController *timer = (TimerController *)g_controllers[CTRL_TIMER];
  UInt64 now = NANOTICKS * timer->getTicks();

  lock();
  if(when < now)
  {
    unlock();
    return;
  }

  curTask->wakeTime = when;
  curTask->next = sleepQ;
  sleepQ = curTask;

  unlock();
  Scheduler::blockTask(sleeping);
}

void nanosleep(UInt64 nano)
{
  TimerController *timer = (TimerController *)g_controllers[CTRL_TIMER];
  UInt64 now = NANOTICKS * timer->getTicks();
  nanosleepUntil(now + nano);
}

void sleep(UInt32 ms)
{
  nanosleep(ms*NANOTICKS);
}

/* FIXME: a real spinlock is needed for SMP */
void lock()
{
  asm("cli");
  ++schedulerSpinlock;
  ++locksHeld;
}

void unlock()
{
  --locksHeld;
  if(locksHeld == 0)
  {
    if(taskSwitchDeferred)
    {
      taskSwitchDeferred = false;
      Scheduler::schedule();
    }
  }

  --schedulerSpinlock;
  if(schedulerSpinlock == 0)
    asm("sti");
}

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
  task->state = readyToRun;
  if(runQ != 0)
  {
    // there is something on the run queue. append this task to the end.
    runQEnd->next = task;
    runQEnd = task;
  } else {
    // there is only one currently running task. pre-empt it.
    // switchTask(task);
    runQ = runQEnd = task;
  }
  Scheduler::unlock();
}

void Scheduler::schedule()
{
  if(locksHeld != 0)
  {
    taskSwitchDeferred = true;
    return;
  }

  updateTimeUsed(curTask);
  if(runQ != 0)
  {
    TaskControlBlock *task = runQ;
    runQ = runQ->next;
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
  tcb->sp -= 136;
  tcb->next = 0;

  if(runQ == 0)
    runQ = tcb;
  if(runQEnd == 0)
    runQEnd = tcb;
  else
  {
    runQEnd->next = tcb;
    runQEnd = tcb;
  }
  return tcb;
}
