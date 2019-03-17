#include <hw/idt.h>

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void setIDTGate(int n, UInt32 handler)
{
    idt[n].low_offset = low16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high16(handler);
}

void setIDT()
{
    idt_reg.base = (UInt32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidtl (%0)" : : "r" (&idt_reg));
}
