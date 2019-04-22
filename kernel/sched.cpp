/*
 * H2 Kernel Scheduler
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/timer.h>
#include <sched.h>
#include <kstdio.h>

TaskControlBlock *curTask = 0;

/* tasks that are ready to run */
TaskControlBlock *readyToRunStart = 0;
TaskControlBlock *readyToRunEnd = 0;

/* tasks that are sleeping */
TaskControlBlock *sleepList = 0;

UInt32 schedulerSpinlock = 0;
UInt32 taskSwitchSpinlock = 0;
bool taskSwitchWasPostponed = false;

CPUTime cputime;
UInt64 lastIdleTime = 0;

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

/* big kernel lock - this can't stay! also: a real spinlock is needed for SMP */
void lock()
{
  asm("cli");
  ++schedulerSpinlock;
  ++taskSwitchSpinlock;
}

void unlock()
{
  --taskSwitchSpinlock;
  if(taskSwitchSpinlock == 0)
  {
    if(taskSwitchWasPostponed)
    {
      taskSwitchWasPostponed = false;
      Scheduler::schedule();
    }
  }

  --schedulerSpinlock;
  if(schedulerSpinlock == 0)
    asm("sti");
}


void nanosleepUntil(UInt64 when)
{
  lock(); // lock the kernel - ugh

  TimerController *timer = (TimerController *)g_controllers[CTRL_TIMER];
  if(when < timer->getTicks()*NANOTICKS)
  {
    unlock();
    return;
  }

  curTask->wakeTime = when;
  curTask->next = sleepList;
  sleepList = curTask;

  unlock();
  Scheduler::blockTask(sleeping);
}

void nanosleep(UInt64 interval)
{
  TimerController *timer = (TimerController *)g_controllers[CTRL_TIMER];
  nanosleepUntil(timer->getTicks()*NANOTICKS + interval);
}

void sleep(UInt32 ms)
{
  nanosleep(ms*1000000);
}

void Scheduler::init()
{
  memset((char *)&cputime, 0, sizeof(cputime));
}

CPUTime *Scheduler::getCPUTime()
{
  return &cputime;
}

void Scheduler::updateTimeUsed()
{
  UInt64 now = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  int elapsed = (now - curTask->lastTime) * 1000; // microseconds? I think.
  curTask->timeUsed += elapsed;
  cputime.sys += elapsed;
  curTask->lastTime = now;
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
  task->next = 0;
  if(readyToRunStart != 0)
  {
    // there is something on the run queue. append this task to the end.
    readyToRunEnd->next = task;
    readyToRunEnd = task;
  }
  else {
    // there is only one currently running task. pre-empt it.
    switchTask(task);
  }
  Scheduler::unlock();
}

void Scheduler::schedule()
{
  if(taskSwitchSpinlock > 0)
  {
    taskSwitchWasPostponed = true;
    return;
  }

  if(readyToRunStart != 0)
  {
    TaskControlBlock *task = readyToRunStart;
    readyToRunStart = task->next;

    updateTimeUsed();
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