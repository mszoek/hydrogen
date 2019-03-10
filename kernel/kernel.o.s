	.file	"kernel.cpp"
	.text
.Ltext0:
	.data
	.align 4
	.type	_ZL12KERN_VERSION, @object
	.size	_ZL12KERN_VERSION, 4
_ZL12KERN_VERSION:
	.long	196608
	.section	.rodata
.LC0:
	.string	" KB memory"
.LC1:
	.string	"; memory map loaded"
.LC2:
	.string	"\n\nisrInstall()\n"
.LC3:
	.string	"initKeyboard()\n"
.LC4:
	.string	"initTimer()\n"
.LC5:
	.string	"pmmInit()\n"
.LC6:
	.string	"Starting shell\n"
	.text
	.globl	kernelMain
	.type	kernelMain, @function
kernelMain:
.LFB0:
	.file 1 "kernel/kernel.cpp"
	.loc 1 26 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$104, %esp
	.loc 1 28 0
	movl	$0, -12(%ebp)
	.loc 1 29 0
	movl	$0, -16(%ebp)
	movl	$0, -20(%ebp)
	.loc 1 31 0
	movl	$0, -24(%ebp)
	.loc 1 33 0
	subl	$12, %esp
	pushl	12(%ebp)
	call	_Z17displayStartupMsgj
	addl	$16, %esp
	.loc 1 36 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L2
	.loc 1 38 0
	movl	8(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	addl	$1024, %eax
	movl	%eax, -12(%ebp)
	.loc 1 39 0
	movl	-12(%ebp), %eax
	subl	$8, %esp
	leal	-38(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 40 0
	subl	$12, %esp
	leal	-38(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 41 0
	subl	$12, %esp
	pushl	$.LC0
	call	_Z6kprintPc
	addl	$16, %esp
.L2:
	.loc 1 43 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L3
	.loc 1 45 0
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 46 0
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 47 0
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-38(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 48 0
	subl	$12, %esp
	pushl	$.LC1
	call	_Z6kprintPc
	addl	$16, %esp
.L3:
	.loc 1 51 0
	subl	$12, %esp
	pushl	$.LC2
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 52 0
	call	_Z10isrInstallv
	.loc 1 53 0
	subl	$12, %esp
	pushl	$.LC3
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 54 0
	call	_Z12initKeyboardv
	.loc 1 55 0
	subl	$12, %esp
	pushl	$.LC4
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 56 0
	subl	$12, %esp
	pushl	$100
	call	_Z9initTimerj
	addl	$16, %esp
	.loc 1 59 0
	subl	$12, %esp
	pushl	$.LC5
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 60 0
	movl	-16(%ebp), %eax
	subl	$12, %esp
	pushl	-20(%ebp)
	pushl	%eax
	pushl	12(%ebp)
	pushl	$16777216
	pushl	-12(%ebp)
	call	_Z7pmmInitjjjP10regionInfoj
	addl	$32, %esp
	.loc 1 62 0
	subl	$12, %esp
	pushl	$.LC6
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 63 0
	call	_Z10shellStartv
	.loc 1 64 0
	call	_Z17displayStatusLinev
	.loc 1 66 0
/APP
/  66 "kernel/kernel.cpp" 1
	sti
/  0 "" 2
	.loc 1 68 0
/NO_APP
	subl	$4, %esp
	pushl	$64
	pushl	$0
	leal	-104(%ebp), %eax
	pushl	%eax
	call	_Z6memsetPcci
	addl	$16, %esp
.L9:
.LBB2:
.LBB3:
	.loc 1 71 0
	movl	tickCounter, %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	mull	%edx
	movl	%edx, %eax
	shrl	$5, %eax
	imull	$100, %eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	testl	%eax, %eax
	jne	.L4
.LBB4:
	.loc 1 73 0
	movl	-24(%ebp), %eax
	movl	-104(%ebp,%eax,4), %eax
	testl	%eax, %eax
	je	.L5
	.loc 1 75 0
	movl	-24(%ebp), %eax
	movl	-104(%ebp,%eax,4), %eax
	subl	$12, %esp
	pushl	%eax
	call	_Z7pmmFreePv
	addl	$16, %esp
.L5:
	.loc 1 77 0
	call	_Z8pmmAllocv
	movl	%eax, -28(%ebp)
	.loc 1 78 0
	cmpl	$0, -28(%ebp)
	je	.L6
	.loc 1 80 0
	cmpl	$9, -24(%ebp)
	jg	.L7
	.loc 1 80 0 is_stmt 0 discriminator 1
	movl	-24(%ebp), %eax
	addl	$48, %eax
	movsbl	%al, %eax
	jmp	.L8
.L7:
	.loc 1 80 0 discriminator 2
	movl	-24(%ebp), %eax
	addl	$55, %eax
	movsbl	%al, %eax
.L8:
	.loc 1 80 0 discriminator 4
	subl	$4, %esp
	pushl	$4096
	pushl	%eax
	pushl	-28(%ebp)
	call	_Z6memsetPcci
	addl	$16, %esp
	.loc 1 81 0 is_stmt 1 discriminator 4
	movl	-24(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -24(%ebp)
	movl	-28(%ebp), %edx
	movl	%edx, -104(%ebp,%eax,4)
	.loc 1 82 0 discriminator 4
	cmpl	$15, -24(%ebp)
	jle	.L6
	.loc 1 84 0
	movl	$0, -24(%ebp)
.L6:
	.loc 1 89 0
	call	_Z17displayStatusLinev
.L4:
.LBE4:
.LBE3:
	.loc 1 92 0
	call	_Z15shellCheckInputv
	.loc 1 94 0
/APP
/  94 "kernel/kernel.cpp" 1
	hlt
/  0 "" 2
/NO_APP
.LBE2:
	.loc 1 95 0
	jmp	.L9
	.cfi_endproc
.LFE0:
	.size	kernelMain, .-kernelMain
	.section	.rodata
.LC7:
	.string	"Mem Free: "
.LC8:
	.string	" blocks Uptime: "
	.text
	.globl	_Z17displayStatusLinev
	.type	_Z17displayStatusLinev, @function
_Z17displayStatusLinev:
.LFB1:
	.loc 1 99 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$132, %esp
	.cfi_offset 3, -12
	.loc 1 104 0
	call	_Z15getCursorOffsetv
	movl	%eax, -12(%ebp)
	.loc 1 106 0
	subl	$4, %esp
	pushl	$81
	pushl	$0
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6memsetPcci
	addl	$16, %esp
	.loc 1 107 0
	subl	$4, %esp
	pushl	$10
	pushl	$.LC7
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 108 0
	call	_Z16pmmMemFreeBlocksv
	movl	%eax, %edx
	subl	$8, %esp
	leal	-41(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 109 0
	subl	$12, %esp
	leal	-41(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %ebx
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %edx
	leal	-122(%ebp), %eax
	addl	%eax, %edx
	subl	$4, %esp
	pushl	%ebx
	leal	-41(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 110 0
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %edx
	leal	-122(%ebp), %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	$16
	pushl	$.LC8
	pushl	%eax
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 111 0
	movl	tickCounter, %eax
	movl	$1374389535, %edx
	mull	%edx
	movl	%edx, %eax
	shrl	$5, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-41(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 112 0
	subl	$12, %esp
	leal	-41(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %ebx
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %edx
	leal	-122(%ebp), %eax
	addl	%eax, %edx
	subl	$4, %esp
	pushl	%ebx
	leal	-41(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 113 0
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	.loc 1 114 0
	leal	-122(%ebp), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	movb	$115, (%eax)
	.loc 1 115 0
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movb	$0, -122(%ebp,%eax)
	.loc 1 116 0
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	$79, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %ebx
	subl	$12, %esp
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z6strlenPc
	addl	$16, %esp
	movl	%eax, %edx
	leal	-122(%ebp), %eax
	addl	%edx, %eax
	subl	$4, %esp
	pushl	%ebx
	pushl	$32
	pushl	%eax
	call	_Z6memsetPcci
	addl	$16, %esp
	.loc 1 117 0
	pushl	$94
	pushl	$0
	pushl	$0
	leal	-122(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 119 0
	subl	$12, %esp
	pushl	-12(%ebp)
	call	_Z15setCursorOffseti
	addl	$16, %esp
	.loc 1 120 0
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z17displayStatusLinev, .-_Z17displayStatusLinev
	.section	.rodata
.LC9:
	.string	"."
.LC10:
	.string	" ["
.LC11:
	.string	" bytes @ 0x1000000]\n"
	.align 4
.LC12:
	.string	"Copyright (C) 2017-2019 H2. All Rights Reserved!\n\n"
	.text
	.globl	_Z17displayStartupMsgj
	.type	_Z17displayStartupMsgj, @function
_Z17displayStartupMsgj:
.LFB2:
	.loc 1 123 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 124 0
	movl	$1397699144, -31(%ebp)
	movl	$1919240992, -27(%ebp)
	movl	$543974766, -23(%ebp)
	movl	$1918989395, -19(%ebp)
	movl	$560227700, -15(%ebp)
	movw	$30240, -11(%ebp)
	movb	$0, -9(%ebp)
	.loc 1 125 0
	subl	$12, %esp
	pushl	$7
	call	_Z11clearScreenc
	addl	$16, %esp
	.loc 1 126 0
	subl	$12, %esp
	pushl	$7
	call	_Z15defaultTextAttrc
	addl	$16, %esp
	.loc 1 127 0
	pushl	$15
	pushl	$2
	pushl	$0
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 128 0
	movl	_ZL12KERN_VERSION, %eax
	shrl	$24, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-31(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 129 0
	pushl	$15
	pushl	$-1
	pushl	$-1
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 130 0
	subl	$12, %esp
	pushl	$.LC9
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 131 0
	movl	_ZL12KERN_VERSION, %eax
	shrl	$16, %eax
	movzbl	%al, %eax
	subl	$8, %esp
	leal	-31(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 132 0
	pushl	$15
	pushl	$-1
	pushl	$-1
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 133 0
	subl	$12, %esp
	pushl	$.LC9
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 134 0
	movl	_ZL12KERN_VERSION, %eax
	shrl	$8, %eax
	movzbl	%al, %eax
	subl	$8, %esp
	leal	-31(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 135 0
	pushl	$15
	pushl	$-1
	pushl	$-1
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 136 0
	subl	$12, %esp
	pushl	$.LC9
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 137 0
	movl	_ZL12KERN_VERSION, %eax
	movzbl	%al, %eax
	subl	$8, %esp
	leal	-31(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 138 0
	pushl	$15
	pushl	$-1
	pushl	$-1
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 139 0
	subl	$12, %esp
	pushl	$.LC10
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 140 0
	movl	8(%ebp), %eax
	subl	$8, %esp
	leal	-31(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 141 0
	subl	$12, %esp
	leal	-31(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 142 0
	subl	$12, %esp
	pushl	$.LC11
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 143 0
	pushl	$15
	pushl	$-1
	pushl	$-1
	pushl	$.LC12
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 144 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z17displayStartupMsgj, .-_Z17displayStartupMsgj
.Letext0:
	.file 2 "includes/hw/types.h"
	.file 3 "includes/hw/idt.h"
	.file 4 "includes/bootinfo.h"
	.file 5 "includes/kversion.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x397
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF49
	.byte	0x4
	.long	.LASF50
	.long	.LASF51
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
	.byte	0x8
	.byte	0x3
	.byte	0xa
	.long	.LASF15
	.long	0xc7
	.uleb128 0x6
	.long	.LASF10
	.byte	0x3
	.byte	0xb
	.long	0x4c
	.byte	0
	.uleb128 0x7
	.string	"sel"
	.byte	0x3
	.byte	0xc
	.long	0x4c
	.byte	0x2
	.uleb128 0x6
	.long	.LASF11
	.byte	0x3
	.byte	0xd
	.long	0x65
	.byte	0x4
	.uleb128 0x6
	.long	.LASF12
	.byte	0x3
	.byte	0x13
	.long	0x65
	.byte	0x5
	.uleb128 0x6
	.long	.LASF13
	.byte	0x3
	.byte	0x14
	.long	0x4c
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.long	.LASF14
	.byte	0x3
	.byte	0x15
	.long	0x7e
	.uleb128 0x5
	.byte	0x6
	.byte	0x3
	.byte	0x19
	.long	.LASF16
	.long	0xf7
	.uleb128 0x6
	.long	.LASF17
	.byte	0x3
	.byte	0x1a
	.long	0x4c
	.byte	0
	.uleb128 0x6
	.long	.LASF18
	.byte	0x3
	.byte	0x1b
	.long	0x33
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.long	.LASF19
	.byte	0x3
	.byte	0x1c
	.long	0xd2
	.uleb128 0x8
	.long	0xc7
	.long	0x112
	.uleb128 0x9
	.long	0x112
	.byte	0xff
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF20
	.uleb128 0xa
	.string	"idt"
	.byte	0x3
	.byte	0x1f
	.long	0x102
	.uleb128 0xb
	.long	.LASF21
	.byte	0x3
	.byte	0x20
	.long	0xf7
	.uleb128 0xc
	.long	.LASF36
	.byte	0x5
	.byte	0x7
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	_ZL12KERN_VERSION
	.uleb128 0xd
	.long	.LASF52
	.byte	0x44
	.byte	0x4
	.byte	0x2f
	.long	0x1f5
	.uleb128 0x6
	.long	.LASF12
	.byte	0x4
	.byte	0x31
	.long	0x3e
	.byte	0
	.uleb128 0x6
	.long	.LASF22
	.byte	0x4
	.byte	0x32
	.long	0x3e
	.byte	0x4
	.uleb128 0x6
	.long	.LASF23
	.byte	0x4
	.byte	0x33
	.long	0x3e
	.byte	0x8
	.uleb128 0x6
	.long	.LASF24
	.byte	0x4
	.byte	0x34
	.long	0x3e
	.byte	0xc
	.uleb128 0x6
	.long	.LASF25
	.byte	0x4
	.byte	0x35
	.long	0x3e
	.byte	0x10
	.uleb128 0x6
	.long	.LASF26
	.byte	0x4
	.byte	0x36
	.long	0x3e
	.byte	0x14
	.uleb128 0x6
	.long	.LASF27
	.byte	0x4
	.byte	0x37
	.long	0x3e
	.byte	0x18
	.uleb128 0x6
	.long	.LASF28
	.byte	0x4
	.byte	0x38
	.long	0x1f5
	.byte	0x1c
	.uleb128 0x6
	.long	.LASF29
	.byte	0x4
	.byte	0x39
	.long	0x3e
	.byte	0x2c
	.uleb128 0x6
	.long	.LASF30
	.byte	0x4
	.byte	0x3a
	.long	0x3e
	.byte	0x30
	.uleb128 0x6
	.long	.LASF31
	.byte	0x4
	.byte	0x3b
	.long	0x3e
	.byte	0x34
	.uleb128 0x6
	.long	.LASF32
	.byte	0x4
	.byte	0x3c
	.long	0x3e
	.byte	0x38
	.uleb128 0x6
	.long	.LASF33
	.byte	0x4
	.byte	0x3d
	.long	0x3e
	.byte	0x3c
	.uleb128 0x6
	.long	.LASF34
	.byte	0x4
	.byte	0x3e
	.long	0x3e
	.byte	0x40
	.byte	0
	.uleb128 0x8
	.long	0x3e
	.long	0x205
	.uleb128 0x9
	.long	0x112
	.byte	0x3
	.byte	0
	.uleb128 0xb
	.long	.LASF35
	.byte	0x1
	.byte	0x12
	.long	0x33
	.uleb128 0xe
	.long	.LASF39
	.byte	0x1
	.byte	0x7a
	.long	.LASF41
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x246
	.uleb128 0xf
	.long	.LASF45
	.byte	0x1
	.byte	0x7a
	.long	0x3e
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xc
	.long	.LASF37
	.byte	0x1
	.byte	0x7c
	.long	0x246
	.uleb128 0x2
	.byte	0x91
	.sleb128 -39
	.byte	0
	.uleb128 0x8
	.long	0x256
	.long	0x256
	.uleb128 0x9
	.long	0x112
	.byte	0x16
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF38
	.uleb128 0xe
	.long	.LASF40
	.byte	0x1
	.byte	0x62
	.long	.LASF42
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x2b7
	.uleb128 0xc
	.long	.LASF43
	.byte	0x1
	.byte	0x64
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x10
	.string	"i"
	.byte	0x1
	.byte	0x64
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.long	.LASF53
	.byte	0x1
	.byte	0x65
	.long	0x256
	.uleb128 0x10
	.string	"s"
	.byte	0x1
	.byte	0x66
	.long	0x2b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -49
	.uleb128 0xc
	.long	.LASF44
	.byte	0x1
	.byte	0x66
	.long	0x2c7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -130
	.byte	0
	.uleb128 0x8
	.long	0x256
	.long	0x2c7
	.uleb128 0x9
	.long	0x112
	.byte	0x18
	.byte	0
	.uleb128 0x8
	.long	0x256
	.long	0x2d7
	.uleb128 0x9
	.long	0x112
	.byte	0x50
	.byte	0
	.uleb128 0x12
	.long	.LASF54
	.byte	0x1
	.byte	0x19
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x372
	.uleb128 0xf
	.long	.LASF46
	.byte	0x1
	.byte	0x19
	.long	0x372
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xf
	.long	.LASF45
	.byte	0x1
	.byte	0x19
	.long	0x3e
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x10
	.string	"buf"
	.byte	0x1
	.byte	0x1b
	.long	0x378
	.uleb128 0x2
	.byte	0x91
	.sleb128 -46
	.uleb128 0x10
	.string	"mem"
	.byte	0x1
	.byte	0x1c
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.long	.LASF47
	.byte	0x1
	.byte	0x1d
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.long	.LASF29
	.byte	0x1
	.byte	0x1d
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xc
	.long	.LASF48
	.byte	0x1
	.byte	0x1e
	.long	0x388
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x10
	.string	"i"
	.byte	0x1
	.byte	0x1f
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x13
	.long	.LBB4
	.long	.LBE4-.LBB4
	.uleb128 0x10
	.string	"p"
	.byte	0x1
	.byte	0x4d
	.long	0x398
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.byte	0
	.uleb128 0x14
	.byte	0x4
	.long	0x140
	.uleb128 0x8
	.long	0x256
	.long	0x388
	.uleb128 0x9
	.long	0x112
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.long	0x33
	.long	0x398
	.uleb128 0x9
	.long	0x112
	.byte	0xf
	.byte	0
	.uleb128 0x15
	.byte	0x4
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
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
.LASF1:
	.string	"long long int"
.LASF52:
	.string	"multiboot_info"
.LASF10:
	.string	"low_offset"
.LASF14:
	.string	"idt_gate_t"
.LASF37:
	.string	"msgStartup"
.LASF23:
	.string	"memHi"
.LASF41:
	.string	"_Z17displayStartupMsgj"
.LASF28:
	.string	"syms"
.LASF21:
	.string	"idt_reg"
.LASF40:
	.string	"displayStatusLine"
.LASF25:
	.string	"cmdLine"
.LASF29:
	.string	"mmapLen"
.LASF17:
	.string	"limit"
.LASF33:
	.string	"cfgTable"
.LASF34:
	.string	"loaderName"
.LASF31:
	.string	"drivesLen"
.LASF8:
	.string	"unsigned char"
.LASF48:
	.string	"pages"
.LASF43:
	.string	"curpos"
.LASF18:
	.string	"base"
.LASF5:
	.string	"short unsigned int"
.LASF24:
	.string	"bootDev"
.LASF15:
	.string	"10idt_gate_t"
.LASF35:
	.string	"tickCounter"
.LASF39:
	.string	"displayStartupMsg"
.LASF54:
	.string	"kernelMain"
.LASF47:
	.string	"mmap"
.LASF20:
	.string	"long unsigned int"
.LASF11:
	.string	"always0"
.LASF53:
	.string	"attr"
.LASF30:
	.string	"mmapAddr"
.LASF46:
	.string	"binf"
.LASF2:
	.string	"unsigned int"
.LASF12:
	.string	"flags"
.LASF26:
	.string	"modsCount"
.LASF42:
	.string	"_Z17displayStatusLinev"
.LASF0:
	.string	"long long unsigned int"
.LASF44:
	.string	"line"
.LASF4:
	.string	"UInt16"
.LASF3:
	.string	"UInt32"
.LASF22:
	.string	"memLo"
.LASF16:
	.string	"14idt_register_t"
.LASF27:
	.string	"modsAddr"
.LASF50:
	.string	"kernel/kernel.cpp"
.LASF38:
	.string	"char"
.LASF49:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF36:
	.string	"KERN_VERSION"
.LASF6:
	.string	"short int"
.LASF51:
	.string	"/home/alexis/src/hydrogen"
.LASF7:
	.string	"UInt8"
.LASF13:
	.string	"high_offset"
.LASF19:
	.string	"idt_register_t"
.LASF9:
	.string	"signed char"
.LASF45:
	.string	"size"
.LASF32:
	.string	"drivesAddr"
	.ident	"GCC: (GNU) 7.2.0"
