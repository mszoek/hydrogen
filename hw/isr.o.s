	.file	"isr.cpp"
	.text
.Ltext0:
	.globl	interruptHandlers
	.section	.bss
	.align 32
	.type	interruptHandlers, @object
	.size	interruptHandlers, 1024
interruptHandlers:
	.zero	1024
	.text
	.globl	_Z10isrInstallv
	.type	_Z10isrInstallv, @function
_Z10isrInstallv:
.LFB0:
	.file 1 "hw/isr.cpp"
	.loc 1 12 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 13 0
	movl	$isr0, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$0
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 14 0
	movl	$isr1, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$1
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 15 0
	movl	$isr2, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$2
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 16 0
	movl	$isr3, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$3
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 17 0
	movl	$isr4, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$4
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 18 0
	movl	$isr5, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$5
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 19 0
	movl	$isr6, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$6
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 20 0
	movl	$isr7, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$7
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 21 0
	movl	$isr8, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$8
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 22 0
	movl	$isr9, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$9
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 23 0
	movl	$isr10, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$10
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 24 0
	movl	$isr11, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$11
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 25 0
	movl	$isr12, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$12
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 26 0
	movl	$isr13, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$13
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 27 0
	movl	$isr14, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$14
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 28 0
	movl	$isr15, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$15
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 29 0
	movl	$isr16, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$16
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 30 0
	movl	$isr17, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$17
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 31 0
	movl	$isr18, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$18
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 32 0
	movl	$isr19, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$19
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 33 0
	movl	$isr20, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$20
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 34 0
	movl	$isr21, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$21
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 35 0
	movl	$isr22, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$22
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 36 0
	movl	$isr23, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$23
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 37 0
	movl	$isr24, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$24
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 38 0
	movl	$isr25, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$25
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 39 0
	movl	$isr26, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$26
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 40 0
	movl	$isr27, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$27
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 41 0
	movl	$isr28, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$28
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 42 0
	movl	$isr29, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$29
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 43 0
	movl	$isr30, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$30
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 44 0
	movl	$isr31, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$31
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 47 0
	subl	$8, %esp
	pushl	$17
	pushl	$32
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 48 0
	subl	$8, %esp
	pushl	$17
	pushl	$160
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 49 0
	subl	$8, %esp
	pushl	$32
	pushl	$33
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 50 0
	subl	$8, %esp
	pushl	$40
	pushl	$161
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 51 0
	subl	$8, %esp
	pushl	$4
	pushl	$33
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 52 0
	subl	$8, %esp
	pushl	$2
	pushl	$161
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 53 0
	subl	$8, %esp
	pushl	$1
	pushl	$33
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 54 0
	subl	$8, %esp
	pushl	$1
	pushl	$161
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 55 0
	subl	$8, %esp
	pushl	$0
	pushl	$33
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 56 0
	subl	$8, %esp
	pushl	$0
	pushl	$161
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 59 0
	movl	$irq0, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$32
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 60 0
	movl	$irq1, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$33
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 61 0
	movl	$irq2, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$34
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 62 0
	movl	$irq3, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$35
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 63 0
	movl	$irq4, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$36
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 64 0
	movl	$irq5, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$37
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 65 0
	movl	$irq6, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$38
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 66 0
	movl	$irq7, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$39
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 67 0
	movl	$irq8, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$40
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 68 0
	movl	$irq9, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$41
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 69 0
	movl	$irq10, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$42
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 70 0
	movl	$irq11, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$43
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 71 0
	movl	$irq12, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$44
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 72 0
	movl	$irq13, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$45
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 73 0
	movl	$irq14, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$46
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 74 0
	movl	$irq15, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$47
	call	_Z10setIDTGateij
	addl	$16, %esp
	.loc 1 76 0
	call	_Z6setIDTv
	.loc 1 77 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z10isrInstallv, .-_Z10isrInstallv
	.globl	exceptionMessages
	.section	.rodata
.LC0:
	.string	"Division By Zero"
.LC1:
	.string	"Debug"
.LC2:
	.string	"Non Maskable Interrupt"
.LC3:
	.string	"Breakpoint"
.LC4:
	.string	"Into Detected Overflow"
.LC5:
	.string	"Out of Bounds"
.LC6:
	.string	"Invalid Opcode"
.LC7:
	.string	"No Coprocessor"
.LC8:
	.string	"Double Fault"
.LC9:
	.string	"Coprocessor Segment Overrun"
.LC10:
	.string	"Bad TSS"
.LC11:
	.string	"Segment Not Present"
.LC12:
	.string	"Stack Fault"
.LC13:
	.string	"General Protection Fault"
.LC14:
	.string	"Page Fault"
.LC15:
	.string	"Unknown Interrupt"
.LC16:
	.string	"Coprocessor Fault"
.LC17:
	.string	"Alignment Check"
.LC18:
	.string	"Machine Check"
.LC19:
	.string	"Reserved"
	.data
	.align 32
	.type	exceptionMessages, @object
	.size	exceptionMessages, 128
exceptionMessages:
	.long	.LC0
	.long	.LC1
	.long	.LC2
	.long	.LC3
	.long	.LC4
	.long	.LC5
	.long	.LC6
	.long	.LC7
	.long	.LC8
	.long	.LC9
	.long	.LC10
	.long	.LC11
	.long	.LC12
	.long	.LC13
	.long	.LC14
	.long	.LC15
	.long	.LC16
	.long	.LC17
	.long	.LC18
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.long	.LC19
	.section	.rodata
.LC20:
	.string	"CPU Exception "
.LC21:
	.string	": "
.LC22:
	.string	"\n"
	.text
	.globl	isrHandler
	.type	isrHandler, @function
isrHandler:
.LFB1:
	.loc 1 119 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 120 0
	subl	$12, %esp
	pushl	$.LC20
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 122 0
	movl	44(%ebp), %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-11(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 123 0
	subl	$12, %esp
	leal	-11(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 124 0
	subl	$12, %esp
	pushl	$.LC21
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 125 0
	movl	44(%ebp), %eax
	movl	exceptionMessages(,%eax,4), %eax
	subl	$12, %esp
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 126 0
	subl	$12, %esp
	pushl	$.LC22
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 127 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	isrHandler, .-isrHandler
	.globl	_Z24registerInterruptHandlerhPFv11registers_tE
	.type	_Z24registerInterruptHandlerhPFv11registers_tE, @function
_Z24registerInterruptHandlerhPFv11registers_tE:
.LFB2:
	.loc 1 130 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	8(%ebp), %eax
	movb	%al, -4(%ebp)
	.loc 1 131 0
	movzbl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, interruptHandlers(,%eax,4)
	.loc 1 132 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z24registerInterruptHandlerhPFv11registers_tE, .-_Z24registerInterruptHandlerhPFv11registers_tE
	.globl	irqHandler
	.type	irqHandler, @function
irqHandler:
.LFB3:
	.loc 1 135 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 138 0
	movl	44(%ebp), %eax
	cmpl	$39, %eax
	jbe	.L5
	.loc 1 138 0 is_stmt 0 discriminator 1
	subl	$8, %esp
	pushl	$32
	pushl	$160
	call	_Z11portByteOutth
	addl	$16, %esp
.L5:
	.loc 1 139 0 is_stmt 1
	subl	$8, %esp
	pushl	$32
	pushl	$32
	call	_Z11portByteOutth
	addl	$16, %esp
.LBB2:
	.loc 1 142 0
	movl	44(%ebp), %eax
	movl	interruptHandlers(,%eax,4), %eax
	testl	%eax, %eax
	je	.L7
.LBB3:
	.loc 1 144 0
	movl	44(%ebp), %eax
	movl	interruptHandlers(,%eax,4), %eax
	movl	%eax, -12(%ebp)
	.loc 1 145 0
	pushl	68(%ebp)
	pushl	64(%ebp)
	pushl	60(%ebp)
	pushl	56(%ebp)
	pushl	52(%ebp)
	pushl	48(%ebp)
	pushl	44(%ebp)
	pushl	40(%ebp)
	pushl	36(%ebp)
	pushl	32(%ebp)
	pushl	28(%ebp)
	pushl	24(%ebp)
	pushl	20(%ebp)
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	movl	-12(%ebp), %eax
	call	*%eax
.LVL0:
	addl	$64, %esp
.L7:
.LBE3:
.LBE2:
	.loc 1 147 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	irqHandler, .-irqHandler
.Letext0:
	.file 2 "includes/hw/types.h"
	.file 3 "includes/hw/isr.h"
	.file 4 "includes/hw/idt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x32d
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF35
	.byte	0x4
	.long	.LASF36
	.long	.LASF37
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF3
	.byte	0x2
	.byte	0x8
	.long	0x3e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF4
	.byte	0x2
	.byte	0xa
	.long	0x57
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF6
	.uleb128 0x3
	.long	.LASF7
	.byte	0x2
	.byte	0xc
	.long	0x70
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF8
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x5
	.byte	0x40
	.byte	0x3
	.byte	0x4b
	.long	.LASF16
	.long	0x148
	.uleb128 0x6
	.string	"ds"
	.byte	0x3
	.byte	0x4c
	.long	0x33
	.byte	0
	.uleb128 0x6
	.string	"edi"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x4
	.uleb128 0x6
	.string	"esi"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x8
	.uleb128 0x6
	.string	"ebp"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0xc
	.uleb128 0x6
	.string	"esp"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x10
	.uleb128 0x6
	.string	"ebx"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x14
	.uleb128 0x6
	.string	"edx"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x18
	.uleb128 0x6
	.string	"ecx"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x1c
	.uleb128 0x6
	.string	"eax"
	.byte	0x3
	.byte	0x4d
	.long	0x33
	.byte	0x20
	.uleb128 0x7
	.long	.LASF10
	.byte	0x3
	.byte	0x4e
	.long	0x33
	.byte	0x24
	.uleb128 0x7
	.long	.LASF11
	.byte	0x3
	.byte	0x4e
	.long	0x33
	.byte	0x28
	.uleb128 0x6
	.string	"eip"
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x2c
	.uleb128 0x6
	.string	"cs"
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x30
	.uleb128 0x7
	.long	.LASF12
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x34
	.uleb128 0x7
	.long	.LASF13
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x38
	.uleb128 0x6
	.string	"ss"
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x3c
	.byte	0
	.uleb128 0x3
	.long	.LASF14
	.byte	0x3
	.byte	0x50
	.long	0x7e
	.uleb128 0x3
	.long	.LASF15
	.byte	0x3
	.byte	0x55
	.long	0x15e
	.uleb128 0x8
	.byte	0x4
	.long	0x164
	.uleb128 0x9
	.long	0x16f
	.uleb128 0xa
	.long	0x148
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0x4
	.byte	0xa
	.long	.LASF17
	.long	0x1b8
	.uleb128 0x7
	.long	.LASF18
	.byte	0x4
	.byte	0xb
	.long	0x4c
	.byte	0
	.uleb128 0x6
	.string	"sel"
	.byte	0x4
	.byte	0xc
	.long	0x4c
	.byte	0x2
	.uleb128 0x7
	.long	.LASF19
	.byte	0x4
	.byte	0xd
	.long	0x65
	.byte	0x4
	.uleb128 0x7
	.long	.LASF20
	.byte	0x4
	.byte	0x13
	.long	0x65
	.byte	0x5
	.uleb128 0x7
	.long	.LASF21
	.byte	0x4
	.byte	0x14
	.long	0x4c
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.long	.LASF22
	.byte	0x4
	.byte	0x15
	.long	0x16f
	.uleb128 0x5
	.byte	0x6
	.byte	0x4
	.byte	0x19
	.long	.LASF23
	.long	0x1e8
	.uleb128 0x7
	.long	.LASF24
	.byte	0x4
	.byte	0x1a
	.long	0x4c
	.byte	0
	.uleb128 0x7
	.long	.LASF25
	.byte	0x4
	.byte	0x1b
	.long	0x33
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.long	.LASF26
	.byte	0x4
	.byte	0x1c
	.long	0x1c3
	.uleb128 0xb
	.long	0x1b8
	.long	0x203
	.uleb128 0xc
	.long	0x203
	.byte	0xff
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF27
	.uleb128 0xd
	.string	"idt"
	.byte	0x4
	.byte	0x1f
	.long	0x1f3
	.uleb128 0xe
	.long	.LASF28
	.byte	0x4
	.byte	0x20
	.long	0x1e8
	.uleb128 0xb
	.long	0x153
	.long	0x230
	.uleb128 0xc
	.long	0x203
	.byte	0xff
	.byte	0
	.uleb128 0xf
	.long	.LASF29
	.byte	0x1
	.byte	0x7
	.long	0x220
	.uleb128 0x5
	.byte	0x3
	.long	interruptHandlers
	.uleb128 0xb
	.long	0x251
	.long	0x251
	.uleb128 0xc
	.long	0x203
	.byte	0x1f
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0x257
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF30
	.uleb128 0xf
	.long	.LASF31
	.byte	0x1
	.byte	0x50
	.long	0x241
	.uleb128 0x5
	.byte	0x3
	.long	exceptionMessages
	.uleb128 0x10
	.long	.LASF33
	.byte	0x1
	.byte	0x86
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x2a9
	.uleb128 0x11
	.string	"r"
	.byte	0x1
	.byte	0x86
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x12
	.long	.LBB3
	.long	.LBE3-.LBB3
	.uleb128 0x13
	.long	.LASF32
	.byte	0x1
	.byte	0x90
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x14
	.long	.LASF38
	.byte	0x1
	.byte	0x81
	.long	.LASF39
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x2dd
	.uleb128 0x11
	.string	"n"
	.byte	0x1
	.byte	0x81
	.long	0x65
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x15
	.long	.LASF32
	.byte	0x1
	.byte	0x81
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x10
	.long	.LASF34
	.byte	0x1
	.byte	0x76
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x30b
	.uleb128 0x11
	.string	"r"
	.byte	0x1
	.byte	0x76
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x16
	.string	"s"
	.byte	0x1
	.byte	0x79
	.long	0x30b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -19
	.byte	0
	.uleb128 0xb
	.long	0x257
	.long	0x31b
	.uleb128 0xc
	.long	0x203
	.byte	0x2
	.byte	0
	.uleb128 0x17
	.long	.LASF40
	.byte	0x1
	.byte	0xb
	.long	.LASF41
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF17:
	.string	"10idt_gate_t"
.LASF22:
	.string	"idt_gate_t"
.LASF11:
	.string	"err_code"
.LASF31:
	.string	"exceptionMessages"
.LASF40:
	.string	"isrInstall"
.LASF13:
	.string	"useresp"
.LASF28:
	.string	"idt_reg"
.LASF19:
	.string	"always0"
.LASF8:
	.string	"unsigned char"
.LASF32:
	.string	"handler"
.LASF25:
	.string	"base"
.LASF5:
	.string	"short unsigned int"
.LASF24:
	.string	"limit"
.LASF29:
	.string	"interruptHandlers"
.LASF30:
	.string	"char"
.LASF27:
	.string	"long unsigned int"
.LASF23:
	.string	"14idt_register_t"
.LASF15:
	.string	"isr_t"
.LASF36:
	.string	"hw/isr.cpp"
.LASF33:
	.string	"irqHandler"
.LASF2:
	.string	"unsigned int"
.LASF20:
	.string	"flags"
.LASF0:
	.string	"long long unsigned int"
.LASF10:
	.string	"int_no"
.LASF4:
	.string	"UInt16"
.LASF3:
	.string	"UInt32"
.LASF38:
	.string	"registerInterruptHandler"
.LASF18:
	.string	"low_offset"
.LASF34:
	.string	"isrHandler"
.LASF14:
	.string	"registers_t"
.LASF12:
	.string	"eflags"
.LASF1:
	.string	"long long int"
.LASF35:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF6:
	.string	"short int"
.LASF41:
	.string	"_Z10isrInstallv"
.LASF37:
	.string	"/home/alexis/src/hydrogen"
.LASF16:
	.string	"11registers_t"
.LASF7:
	.string	"UInt8"
.LASF21:
	.string	"high_offset"
.LASF26:
	.string	"idt_register_t"
.LASF9:
	.string	"signed char"
.LASF39:
	.string	"_Z24registerInterruptHandlerhPFv11registers_tE"
	.ident	"GCC: (GNU) 7.2.0"
