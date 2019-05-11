/*
 * H2 Kernel Scheduler
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <kernel.h>
#include <hw/timer.h>
#include <sched.h>
#include <kstdio.h>

GlobalDescriptorTable *gdt = 0;
TaskStateSegment *tss = 0;

TaskControlBlock *curTask = 0;
TaskControlBlock *runQ = 0;
TaskControlBlock *runQEnd = 0;
TaskControlBlock *sleepQ = 0;
TaskControlBlock *termQ = 0;
TaskControlBlock *waitQ = 0;

TaskControlBlock *reaper = 0;

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

  lock();
  Scheduler::updateTimeUsed();
  curTask->wakeTime = when;
  curTask->next = sleepQ;
  sleepQ = curTask;
  // curTask->state = sleeping;
  Scheduler::blockTask(sleeping);
  unlock();
  // Scheduler::schedule(); // find something else to run
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

// put task on waitQ. Must be unblocked by another task
void wait(void)
{
  Scheduler::updateTimeUsed();
  curTask->next = waitQ;
  waitQ = curTask;
  Scheduler::blockTask(waiting);
}

// remove tcb from waitQ
void unwait(TaskControlBlock *tcb)
{
  TaskControlBlock *task = waitQ;
  waitQ = 0;
  while(task != 0)
  {
    TaskControlBlock *cur = task;
    task = task->next;
    if(cur != tcb)
    {
      cur->next = waitQ;
      waitQ = cur;
    }
  }
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

void Scheduler::init()
{
  /* First, we create a new GDT that has a TSS for each
   * CPU we want to use. By default this is up to 16 cores.
   */

  // 8 bytes per TSS + kernel null, CS, DS. This is equiv to GDT64 + TSS
  gdt = (GlobalDescriptorTable *)malloc(8*MAX_CORES + 48);
  memset((char *)gdt, 0, 8*MAX_CORES + 48);
  gdt[0].limit0 = 0xFFFF;
  gdt[0].limit1 = 0x1;
  gdt[1].access = 0x9A; // 10011010, read/exec
  gdt[1].flags = 0xA; // graularity = 4K, 64-bit CS
  gdt[2].access = 0x92; // 10010010, read/write
  gdt[2].flags = 0x8; // granularity = 4K

  // same things for ring 3
  gdt[3].access = 0xFA; // 11111010, read/exec
  gdt[3].flags = 0xA; // graularity = 4K, 64-bit CS
  gdt[4].access = 0xF2; // 11110010, read/write
  gdt[4].flags = 0x8; // granularity = 4K

  // allocate the TSS memory and initialize one for cpu0
  tss = (TaskStateSegment *)malloc(sizeof(TaskStateSegment));
  memset((char *)tss, 0, sizeof(TaskStateSegment));
  asm("mov %%rsp, %0" : "=m"(tss[0].rsp0));
  tss[0].IOPBAddr = 104;


  // Create a TSS structure and link it to our GDT
  gdt[5].access = 0x89; // 10000010 system seg, read
  gdt[5].flags = 0x4;
  gdt[5].base0 = ((UInt64)&tss[0]) & 0xFFFF;
  gdt[5].base1 = (((UInt64)&tss[0]) & 0xFF0000) >> 16;
  gdt[5].base2 = (((UInt64)&tss[0]) & 0xFF000000) >> 24;
  gdt[5].limit0 = sizeof(TaskStateSegment);

  // load the new GDT and TSS
  GDTReg gdtreg;
  gdtreg.size = 8*MAX_CORES + 48;
  gdtreg.address = (UInt64)gdt;
  asm("lgdt %0; mov $0x10, %%ax; mov %%ax, %%ds; mov %%ax, %%es; mov %%ax, %%fs; mov %%ax, %%ss" :: "m"(gdtreg));
  asm("mov $0x28, %ax; ltr %ax");
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
  else if(curTask->rsp3 != 0)
    cputime.user += elapsed;
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
  ::lock();
  task->state = readyToRun;
  if(runQ != 0)
  {
    // there is something on the run queue. append this task to the end.
    runQEnd->next = task;
    runQEnd = task;
    ::unlock();
  } else {
    // there is only one currently running task. pre-empt it.
    updateTimeUsed();
    task->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks(); // runtime starts now
    ::unlock();
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
    // asm("cli");
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
  tcb->rsp0 = (UInt64)vmm->malloc(KERNEL_STACK_SIZE);
  memset((char *)tcb->rsp0, 0, KERNEL_STACK_SIZE);
  tcb->rsp0 += KERNEL_STACK_SIZE;
  tcb->sp = tcb->rsp0;
  tcb->usersp = 0;
  tcb->lastTime = ((TimerController *)g_controllers[CTRL_TIMER])->getTicks();
  tcb->timeUsed = 0;
  tcb->priority = 1;
  tcb->timeSlice = 1 + tcb->priority;
  tcb->entry = 0;
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

void Scheduler::terminateTask(void)
{
  // close files, free userspace memory, etc
  ::lock();
  curTask->next = termQ;
  termQ = curTask;
  // curTask->state = terminated;
  blockTask(terminated);

  unwait(reaper);
  unblockTask(reaper);
  ::unlock();
}

void Scheduler::taskReaper(void)
{
  TaskControlBlock *task;
  while(1)
  {
    ::lock();
    while(termQ != 0)
    {
      task = termQ;
      termQ = termQ->next;
      free((void *)(task->rsp0 - KERNEL_STACK_SIZE));
      if(task->rsp3 != 0)
        free((void *)(task->rsp3 - USER_STACK_SIZE));
      if(task->entry != 0)
        free((void *)task->entry); // free memory used by process image
      free(task);
    }
    wait();
    ::unlock();
  }
}

TaskControlBlock *Scheduler::createProcess(UInt64 entry, char *name)
{
  TaskControlBlock *user = Scheduler::createTask(switchUserland, name);
  user->rsp3 = (UInt64)malloc(USER_STACK_SIZE);
  memset((char *)user->rsp3, 0, USER_STACK_SIZE);
  user->rsp3 += USER_STACK_SIZE;
  user->usersp = user->rsp3;
  user->entry = entry;
  return user;
}
