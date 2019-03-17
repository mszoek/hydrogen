#include <hw/port_io.h>
#include <hw/isr.h>
#include <hw/idt.h>
#include <kstring.h>
#include <drivers/screen.h>

isr_t interruptHandlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isrInstall()
{
    setIDTGate(0, (UInt32)isr0);
    setIDTGate(1, (UInt32)isr1);
    setIDTGate(2, (UInt32)isr2);
    setIDTGate(3, (UInt32)isr3);
    setIDTGate(4, (UInt32)isr4);
    setIDTGate(5, (UInt32)isr5);
    setIDTGate(6, (UInt32)isr6);
    setIDTGate(7, (UInt32)isr7);
    setIDTGate(8, (UInt32)isr8);
    setIDTGate(9, (UInt32)isr9);
    setIDTGate(10, (UInt32)isr10);
    setIDTGate(11, (UInt32)isr11);
    setIDTGate(12, (UInt32)isr12);
    setIDTGate(13, (UInt32)isr13);
    setIDTGate(14, (UInt32)isr14);
    setIDTGate(15, (UInt32)isr15);
    setIDTGate(16, (UInt32)isr16);
    setIDTGate(17, (UInt32)isr17);
    setIDTGate(18, (UInt32)isr18);
    setIDTGate(19, (UInt32)isr19);
    setIDTGate(20, (UInt32)isr20);
    setIDTGate(21, (UInt32)isr21);
    setIDTGate(22, (UInt32)isr22);
    setIDTGate(23, (UInt32)isr23);
    setIDTGate(24, (UInt32)isr24);
    setIDTGate(25, (UInt32)isr25);
    setIDTGate(26, (UInt32)isr26);
    setIDTGate(27, (UInt32)isr27);
    setIDTGate(28, (UInt32)isr28);
    setIDTGate(29, (UInt32)isr29);
    setIDTGate(30, (UInt32)isr30);
    setIDTGate(31, (UInt32)isr31);

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
    setIDTGate(32, (UInt32)irq0);
    setIDTGate(33, (UInt32)irq1);
    setIDTGate(34, (UInt32)irq2);
    setIDTGate(35, (UInt32)irq3);
    setIDTGate(36, (UInt32)irq4);
    setIDTGate(37, (UInt32)irq5);
    setIDTGate(38, (UInt32)irq6);
    setIDTGate(39, (UInt32)irq7);
    setIDTGate(40, (UInt32)irq8);
    setIDTGate(41, (UInt32)irq9);
    setIDTGate(42, (UInt32)irq10);
    setIDTGate(43, (UInt32)irq11);
    setIDTGate(44, (UInt32)irq12);
    setIDTGate(45, (UInt32)irq13);
    setIDTGate(46, (UInt32)irq14);
    setIDTGate(47, (UInt32)irq15);

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
