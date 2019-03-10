	.file	"timer.cpp"
	.text
.Ltext0:
	.globl	tickCounter
	.section	.bss
	.align 4
	.type	tickCounter, @object
	.size	tickCounter, 4
tickCounter:
	.zero	4
	.text
	.type	_ZL13timerCallback11registers_t, @function
_ZL13timerCallback11registers_t:
.LFB0:
	.file 1 "hw/timer.cpp"
	.loc 1 14 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 15 0
	movl	tickCounter, %eax
	addl	$1, %eax
	movl	%eax, tickCounter
	.loc 1 16 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_ZL13timerCallback11registers_t, .-_ZL13timerCallback11registers_t
	.globl	_Z9initTimerj
	.type	_Z9initTimerj, @function
_Z9initTimerj:
.LFB1:
	.loc 1 19 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 20 0
	subl	$8, %esp
	pushl	$_ZL13timerCallback11registers_t
	pushl	$32
	call	_Z24registerInterruptHandlerhPFv11registers_tE
	addl	$16, %esp
	.loc 1 23 0
	movl	$1193180, %eax
	movl	$0, %edx
	divl	8(%ebp)
	movl	%eax, -12(%ebp)
	.loc 1 24 0
	movl	-12(%ebp), %eax
	movb	%al, -13(%ebp)
	.loc 1 25 0
	movl	-12(%ebp), %eax
	shrl	$8, %eax
	movb	%al, -14(%ebp)
	.loc 1 26 0
	subl	$8, %esp
	pushl	$54
	pushl	$67
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 27 0
	movzbl	-13(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$64
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 28 0
	movzbl	-14(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$64
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 29 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z9initTimerj, .-_Z9initTimerj
.Letext0:
	.file 2 "includes/hw/types.h"
	.file 3 "includes/hw/isr.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1c7
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF17
	.byte	0x4
	.long	.LASF18
	.long	.LASF19
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
	.long	.LASF5
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
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF4
	.uleb128 0x3
	.long	.LASF6
	.byte	0x2
	.byte	0xc
	.long	0x65
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF8
	.uleb128 0x5
	.byte	0x40
	.byte	0x3
	.byte	0x4b
	.long	.LASF20
	.long	0x13d
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
	.long	.LASF9
	.byte	0x3
	.byte	0x4e
	.long	0x33
	.byte	0x24
	.uleb128 0x7
	.long	.LASF10
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
	.long	.LASF11
	.byte	0x3
	.byte	0x4f
	.long	0x33
	.byte	0x34
	.uleb128 0x7
	.long	.LASF12
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
	.long	.LASF13
	.byte	0x3
	.byte	0x50
	.long	0x73
	.uleb128 0x8
	.long	.LASF21
	.byte	0x1
	.byte	0xb
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	tickCounter
	.uleb128 0x9
	.long	.LASF22
	.byte	0x1
	.byte	0x12
	.long	.LASF23
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x1aa
	.uleb128 0xa
	.string	"Hz"
	.byte	0x1
	.byte	0x12
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xb
	.long	.LASF14
	.byte	0x1
	.byte	0x17
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.string	"low"
	.byte	0x1
	.byte	0x18
	.long	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -21
	.uleb128 0xb
	.long	.LASF15
	.byte	0x1
	.byte	0x19
	.long	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -22
	.byte	0
	.uleb128 0xd
	.long	.LASF24
	.byte	0x1
	.byte	0xd
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.long	.LASF16
	.byte	0x1
	.byte	0xd
	.long	0x13d
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
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
	.uleb128 0x9
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
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xe
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
.LASF15:
	.string	"high"
.LASF24:
	.string	"timerCallback"
.LASF10:
	.string	"err_code"
.LASF12:
	.string	"useresp"
.LASF7:
	.string	"unsigned char"
.LASF3:
	.string	"short unsigned int"
.LASF22:
	.string	"initTimer"
.LASF21:
	.string	"tickCounter"
.LASF16:
	.string	"regs"
.LASF18:
	.string	"hw/timer.cpp"
.LASF2:
	.string	"unsigned int"
.LASF0:
	.string	"long long unsigned int"
.LASF14:
	.string	"divisor"
.LASF9:
	.string	"int_no"
.LASF5:
	.string	"UInt32"
.LASF13:
	.string	"registers_t"
.LASF11:
	.string	"eflags"
.LASF1:
	.string	"long long int"
.LASF17:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF4:
	.string	"short int"
.LASF19:
	.string	"/home/alexis/src/hydrogen"
.LASF20:
	.string	"11registers_t"
.LASF6:
	.string	"UInt8"
.LASF8:
	.string	"signed char"
.LASF23:
	.string	"_Z9initTimerj"
	.ident	"GCC: (GNU) 7.2.0"
