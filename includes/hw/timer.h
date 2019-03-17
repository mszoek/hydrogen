/*
 * H2 Timer Controller
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#ifndef TIMER_H
#define TIMER_H

#define KERNEL_HZ 1000

class TimerController
{
public:
    TimerController();
    virtual ~TimerController();

    UInt32 getTicks();
    UInt32 getSeconds();
    void tick();

private:
    UInt32 tickCounter;
};

#endif
