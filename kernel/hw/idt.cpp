/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#include <hw/idt.h>

idtGate idt[IDT_ENTRIES];
idtRegister idt_reg;

/* interrupts 128+ can be called from userspace */
void setIDTGate(int n, UInt64 handler)
{
    idt[n].offset0 = low16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].ist = 0;
    idt[n].flags = (n > 127 ? 0xEE : 0x8E);
    idt[n].offset1 = high16(handler);
    idt[n].offset2 = (handler >> 32);
    idt[n].zero = 0;
}

void setIDT()
{
    idt_reg.base = (UInt64) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idtGate) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}
