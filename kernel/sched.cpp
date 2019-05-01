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

CPUTime cputime;

CPUTime Scheduler::getCPUTime()
{
  return cputime;
}

void nanosleepUntil(UInt64 when)
{
  UInt64 now = NANOTICKS * ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();

  if(when < now)
  {
    return;
  }

  asm("cli");
  Scheduler::updateTimeUsed();
  curTask->wakeTime = when;
  curTask->next = sleepQ;
  curTask->state = sleeping;
  sleepQ = curTask;
  asm("sti");
}

void nanosleep(UInt64 nano)
{
  UInt64 now = NANOTICKS * ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  nanosleepUntil(now + nano);
}

void sleep(UInt32 ms)
{
  nanosleep(ms*NANOTICKS);
}

/* FIXME: a real spinlock is needed for SMP */
void lock()
{
  Scheduler::lock();
  ++locksHeld;
}

void unlock()
{
  --locksHeld;
  Scheduler::unlock();
  if(locksHeld == 0)
  {
    if(taskSwitchDeferred)
    {
      taskSwitchDeferred = false;
      Scheduler::schedule();
    }
  }
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

void Scheduler::updateTimeUsed()
{
  UInt64 now = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  int elapsed = (now - curTask->lastTime) * 1000; // microseconds? I think.
  curTask->timeUsed += elapsed;
  curTask->lastTime = now;
  if(curTask->tid == 1) // idle task
    cputime.idle += elapsed;
  else
    cputime.sys += elapsed;
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
  task->state = readyToRun;
  if(runQ != 0)
  {
    // there is something on the run queue. append this task to the end.
    runQEnd->next = task;
    runQEnd = task;
  } else {
    // there is only one currently running task. pre-empt it.
    updateTimeUsed();
    task->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks(); // runtime starts now
    switchTask(task);
  }
}

void Scheduler::schedule()
{
  if(locksHeld != 0)
  {
    taskSwitchDeferred = true;
    return;
  }

  updateTimeUsed();
  if(runQ != 0)
  {
    asm("cli");
    TaskControlBlock *task = runQ;
    runQ = runQ->next;
    task->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
    switchTask(task);
  }
}

TaskControlBlock *Scheduler::createTask(void (&entry)(), char *name)
{
  static UInt32 taskID = 1;

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

  return tcb;
}
