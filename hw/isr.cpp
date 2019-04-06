/*
 * H2 Interrupt Handling
 * Copyright (C) 2017-2019 Zoe Knox. All rights reserved.
 */

#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/idt.h>
#include <kstdio.h>

isr_t interruptHandlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isrInstall()
{
    setIDTGate(0, (UInt64)isr0);
    setIDTGate(1, (UInt64)isr1);
    setIDTGate(2, (UInt64)isr2);
    setIDTGate(3, (UInt64)isr3);
    setIDTGate(4, (UInt64)isr4);
    setIDTGate(5, (UInt64)isr5);
    setIDTGate(6, (UInt64)isr6);
    setIDTGate(7, (UInt64)isr7);
    setIDTGate(8, (UInt64)isr8);
    setIDTGate(9, (UInt64)isr9);
    setIDTGate(10, (UInt64)isr10);
    setIDTGate(11, (UInt64)isr11);
    setIDTGate(12, (UInt64)isr12);
    setIDTGate(13, (UInt64)isr13);
    setIDTGate(14, (UInt64)isr14);
    setIDTGate(15, (UInt64)isr15);
    setIDTGate(16, (UInt64)isr16);
    setIDTGate(17, (UInt64)isr17);
    setIDTGate(18, (UInt64)isr18);
    setIDTGate(19, (UInt64)isr19);
    setIDTGate(20, (UInt64)isr20);
    setIDTGate(21, (UInt64)isr21);
    setIDTGate(22, (UInt64)isr22);
    setIDTGate(23, (UInt64)isr23);
    setIDTGate(24, (UInt64)isr24);
    setIDTGate(25, (UInt64)isr25);
    setIDTGate(26, (UInt64)isr26);
    setIDTGate(27, (UInt64)isr27);
    setIDTGate(28, (UInt64)isr28);
    setIDTGate(29, (UInt64)isr29);
    setIDTGate(30, (UInt64)isr30);
    setIDTGate(31, (UInt64)isr31);

    // Remap the PIC
    portByteOut(0x20, 0x11);
    portByteOut(0xA0, 0x11);
    portByteOut(0x21, 0x20);
    portByteOut(0xA1, 0x28);
    portByteOut(0x21, 0x04);
    portByteOut(0xA1, 0x02);
    portByteOut(0x21, 0x01);
    portByteOut(0xA1, 0x01);
    portByteOut(0x21, 0x0);
    portByteOut(0xA1, 0x0);

    // Install the IRQs
    setIDTGate(32, (UInt64)irq0);
    setIDTGate(33, (UInt64)irq1);
    setIDTGate(34, (UInt64)irq2);
    setIDTGate(35, (UInt64)irq3);
    setIDTGate(36, (UInt64)irq4);
    setIDTGate(37, (UInt64)irq5);
    setIDTGate(38, (UInt64)irq6);
    setIDTGate(39, (UInt64)irq7);
    setIDTGate(40, (UInt64)irq8);
    setIDTGate(41, (UInt64)irq9);
    setIDTGate(42, (UInt64)irq10);
    setIDTGate(43, (UInt64)irq11);
    setIDTGate(44, (UInt64)irq12);
    setIDTGate(45, (UInt64)irq13);
    setIDTGate(46, (UInt64)irq14);
    setIDTGate(47, (UInt64)irq15);

    setIDT(); // Load with ASM
}

/* To print the message which defines every exception */
char *exceptionMessages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern "C" void isrHandler(registers_t r)
{
    kprintf("CPU Exception %d: %s\n", r.int_no, exceptionMessages[r.int_no]);
    // FIXME: print a kernel stack dump here! (panic message)
}

void registerInterruptHandler(UInt8 n, isr_t handler)
{
    interruptHandlers[n] = handler;
}

extern "C" void irqHandler(registers_t r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) portByteOut(0xA0, 0x20); /* slave */
    portByteOut(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interruptHandlers[r.int_no] != 0)
    {
        isr_t handler = interruptHandlers[r.int_no];
        handler(r);
    }
}
