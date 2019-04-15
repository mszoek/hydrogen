/*
 * H2 Kernel
 * Copyright (C) 2017-2019 Zoe & Alexis Knox. All rights reserved.
 */

#ifndef IDT_H
#define IDT_H

#include <hw/types.h>

/* Segment selectors */
#define KERNEL_CS 0x08

/* How every interrupt gate (handler) is defined */
typedef struct {
    UInt16 offset0; /* Handler address bits 0-15 */
    UInt16 sel; /* Kernel segment selector */
    UInt8 ist; // bits 0-2 = Int Stack Tbl Offset, rest = 0
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    UInt8 flags;
    UInt16 offset1; /* Handler address bits 16-31 */
    UInt32 offset2; /* Handler address bits 32-63 */
    UInt32 zero;    // reserved
} __attribute__((packed)) idtGate;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    UInt16 limit;
    UInt64 base;
} __attribute__((packed)) idtRegister;

#define IDT_ENTRIES 256
extern idtGate idt[IDT_ENTRIES];
extern idtRegister idt_reg;


/* Functions implemented in idt.c */
void setIDTGate(int n, UInt64 handler);
void setIDT();

#endif
