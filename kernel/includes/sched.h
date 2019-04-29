#ifndef SCHED_H
#define SCHED_H

#include <hw/types.h>

#define NANOTICKS 1000000 // ms to ns

// be sure to update switchTask() if these are changed!
typedef enum _TaskState
{
    readyToRun, running, sleeping, waitIO, waitLock, wait 
} TaskState;


// be sure to update switchTask if this struct is changed!
typedef struct _TaskControlBlock
{
/* 0 */ struct _TaskControlBlock *next;
/* 8 */ UInt32 tid;     // task ID
/* 12*/ UInt64 sp;      // address of kernel stack top
/* 20*/ UInt64 usersp;  // address of user stack top (0 for kernel tasks)
/* 28*/ UInt64 vas;     // PML4T address
/* 36*/ UInt8 state;
        UInt8 priority;
        UInt64 timeUsed;
        UInt64 lastTime;
        UInt64 wakeTime;
        char name[48]; 
} __attribute__((packed)) TaskControlBlock;

extern TaskControlBlock *curTask;
extern TaskControlBlock *runQ;
extern TaskControlBlock *runQEnd;
extern TaskControlBlock *sleepQ;
extern "C" void switchTask(TaskControlBlock *task);

/* TEKPORARY Big Kernel Lock (not scheduler lock below) */
void lock();
void unlock();

void nanosleepUntil(UInt64 when);
void nanosleep(UInt64 nano);
void sleep(UInt32 ms);

class Scheduler
{
public:
    static void init();
    static TaskControlBlock *createTask(void (&entry)(), char *name = 0);
    static void updateTimeUsed(TaskControlBlock *task);
    static void blockTask(TaskState state); // block the running task
    static void unblockTask(TaskControlBlock *task);
    static void schedule(); // caller must lock before calling & unlock after
    static void lock();
    static void unlock();
    // static CPUTime *getCPUTime();
};

#endif // SCHED_H