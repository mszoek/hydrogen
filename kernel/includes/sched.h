#ifndef SCHED_H
#define SCHED_H

#include <hw/types.h>

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
        char name[48]; 
} __attribute__((packed)) TaskControlBlock;

extern TaskControlBlock *curTask;
extern "C" void switchTask(TaskControlBlock *task);

class Scheduler
{
public:
    static TaskControlBlock *createTask(void (&entry)(), char *name = 0);
    static void updateTimeUsed(TaskControlBlock *task);
    static void blockTask(TaskState state); // block the running task
    static void unblockTask(TaskControlBlock *task);
    static void schedule(); // caller must lock before calling & unlock after
    static void lock();
    static void unlock();
};

#endif // SCHED_H