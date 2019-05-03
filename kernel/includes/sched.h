#ifndef SCHED_H
#define SCHED_H

#include <hw/types.h>

#define NANOTICKS 1000000 // ms to ns

// be sure to update switchTask() if these are changed!
typedef enum _TaskState
{
    readyToRun, running, sleeping, waitIO, waitLock, wait 
} TaskState;

typedef struct _CPUTime
{
    UInt64 idle;
    UInt64 sys;
    UInt64 iowait;
    UInt64 wait;
} CPUTime;

typedef struct _GlobalDescriptorTable
{
    UInt16 limit0;
    UInt16 base0;
    UInt8 base1;
    UInt8 access;
    UInt8 limit1:4;
    UInt8 flags:4;
    UInt8 base2;
} __attribute__((packed)) GlobalDescriptorTable;

typedef struct _GDTReg
{
    UInt16 size;
    UInt64 address;
} __attribute__((packed)) GDTReg;

extern GlobalDescriptorTable *gdt;

// be sure to update switchTask if this struct is changed!
typedef struct _TaskControlBlock
{
/* 0 */ struct _TaskControlBlock *next;
/* 8 */ UInt32 tid;     // task ID
/* 12*/ UInt64 sp;      // stack pointer
/* 20*/ UInt64 usersp;  // address of user stack top (0 for kernel tasks)
/* 28*/ UInt64 rsp0;    // address of kernel stack top for TSS
/* 36*/ UInt64 vas;     // PML4T address
/* 44*/ UInt8 state;
/* 45*/ UInt8 priority;
/* 46*/ UInt64 timeSlice;
        UInt64 timeUsed;
        UInt64 lastTime;
        UInt64 wakeTime;
        char name[48]; 
} __attribute__((packed)) TaskControlBlock;

typedef struct _TaskStateSegment
{
    UInt32 reserved0;
    UInt64 rsp0;
    UInt64 rsp1;
    UInt64 rsp2;
    UInt64 reserved1;
    UInt64 ist[8];
    UInt64 reserved2;
    UInt16 IOPBAddr;
    UInt16 reserved3;
} __attribute__((packed)) TaskStateSegment;

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
    static void updateTimeUsed();
    static void blockTask(TaskState state); // block the running task
    static void unblockTask(TaskControlBlock *task);
    static void schedule(); // caller must lock before calling & unlock after
    static void lock();
    static void unlock();
    static CPUTime getCPUTime();
};

#endif // SCHED_H