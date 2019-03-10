	.file	"screen.cpp"
	.text
.Ltext0:
	.globl	g_textAttr
	.data
	.type	g_textAttr, @object
	.size	g_textAttr, 1
g_textAttr:
	.byte	15
	.text
	.globl	_Z15defaultTextAttrc
	.type	_Z15defaultTextAttrc, @function
_Z15defaultTextAttrc:
.LFB0:
	.file 1 "drivers/screen.cpp"
	.loc 1 22 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	8(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 23 0
	movzbl	g_textAttr, %eax
	movb	%al, -1(%ebp)
	.loc 1 24 0
	cmpb	$0, -20(%ebp)
	je	.L2
	.loc 1 24 0 is_stmt 0 discriminator 1
	movzbl	-20(%ebp), %eax
	movb	%al, g_textAttr
.L2:
	.loc 1 25 0 is_stmt 1
	movzbl	-1(%ebp), %eax
	.loc 1 26 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z15defaultTextAttrc, .-_Z15defaultTextAttrc
	.globl	_Z8kprintAtPciic
	.type	_Z8kprintAtPciic, @function
_Z8kprintAtPciic:
.LFB1:
	.loc 1 29 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	20(%ebp), %eax
	movb	%al, -28(%ebp)
	.loc 1 31 0
	cmpl	$0, 12(%ebp)
	js	.L5
	.loc 1 31 0 is_stmt 0 discriminator 1
	cmpl	$0, 16(%ebp)
	js	.L5
	.loc 1 33 0 is_stmt 1
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	call	_Z9getOffsetii
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	jmp	.L6
.L5:
	.loc 1 35 0
	call	_Z15getCursorOffsetv
	movl	%eax, -16(%ebp)
	.loc 1 36 0
	subl	$12, %esp
	pushl	-16(%ebp)
	call	_Z12getOffsetRowi
	addl	$16, %esp
	movl	%eax, 16(%ebp)
	.loc 1 37 0
	subl	$12, %esp
	pushl	-16(%ebp)
	call	_Z12getOffsetColi
	addl	$16, %esp
	movl	%eax, 12(%ebp)
.L6:
	.loc 1 40 0
	movl	$0, -12(%ebp)
.L8:
	.loc 1 41 0
	movl	-12(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L9
	.loc 1 43 0
	movsbl	-28(%ebp), %edx
	movl	-12(%ebp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, -12(%ebp)
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	pushl	%edx
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	%eax
	call	_Z9printCharciic
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	.loc 1 44 0
	subl	$12, %esp
	pushl	-16(%ebp)
	call	_Z12getOffsetRowi
	addl	$16, %esp
	movl	%eax, 16(%ebp)
	.loc 1 45 0
	subl	$12, %esp
	pushl	-16(%ebp)
	call	_Z12getOffsetColi
	addl	$16, %esp
	movl	%eax, 12(%ebp)
	.loc 1 41 0
	jmp	.L8
.L9:
	.loc 1 47 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z8kprintAtPciic, .-_Z8kprintAtPciic
	.globl	_Z14printBackspacev
	.type	_Z14printBackspacev, @function
_Z14printBackspacev:
.LFB2:
	.loc 1 50 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 51 0
	call	_Z15getCursorOffsetv
	subl	$2, %eax
	movl	%eax, -12(%ebp)
	.loc 1 52 0
	cmpl	$0, -12(%ebp)
	jns	.L11
	.loc 1 54 0
	movl	$0, -12(%ebp)
.L11:
	.loc 1 56 0
	movl	-12(%ebp), %eax
	addl	$753664, %eax
	movb	$32, (%eax)
	.loc 1 57 0
	subl	$12, %esp
	pushl	-12(%ebp)
	call	_Z15setCursorOffseti
	addl	$16, %esp
	.loc 1 58 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z14printBackspacev, .-_Z14printBackspacev
	.globl	_Z6kprintPc
	.type	_Z6kprintPc, @function
_Z6kprintPc:
.LFB3:
	.loc 1 61 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 62 0
	movzbl	g_textAttr, %eax
	movsbl	%al, %eax
	pushl	%eax
	pushl	$-1
	pushl	$-1
	pushl	8(%ebp)
	call	_Z8kprintAtPciic
	addl	$16, %esp
	.loc 1 63 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	_Z6kprintPc, .-_Z6kprintPc
	.globl	_Z9printCharciic
	.type	_Z9printCharciic, @function
_Z9printCharciic:
.LFB4:
	.loc 1 70 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %edx
	movl	20(%ebp), %eax
	movb	%dl, -28(%ebp)
	movb	%al, -32(%ebp)
	.loc 1 71 0
	movl	$753664, -20(%ebp)
	.loc 1 72 0
	cmpb	$0, -32(%ebp)
	jne	.L14
	.loc 1 72 0 is_stmt 0 discriminator 1
	movb	$15, -32(%ebp)
.L14:
	.loc 1 75 0 is_stmt 1
	cmpl	$79, 12(%ebp)
	jg	.L15
	.loc 1 75 0 is_stmt 0 discriminator 1
	cmpl	$24, 16(%ebp)
	jle	.L16
.L15:
	.loc 1 77 0 is_stmt 1
	movl	-20(%ebp), %eax
	addl	$3998, %eax
	movb	$69, (%eax)
	.loc 1 78 0
	movl	-20(%ebp), %eax
	addl	$3999, %eax
	movb	$79, (%eax)
	.loc 1 79 0
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	call	_Z9getOffsetii
	addl	$16, %esp
	jmp	.L17
.L16:
	.loc 1 83 0
	cmpl	$0, 12(%ebp)
	js	.L18
	.loc 1 83 0 is_stmt 0 discriminator 1
	cmpl	$0, 16(%ebp)
	js	.L18
	.loc 1 83 0 discriminator 2
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	call	_Z9getOffsetii
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	jmp	.L19
.L18:
	.loc 1 84 0 is_stmt 1
	call	_Z15getCursorOffsetv
	movl	%eax, -12(%ebp)
.L19:
	.loc 1 86 0
	cmpb	$10, -28(%ebp)
	jne	.L20
	.loc 1 88 0
	subl	$12, %esp
	pushl	-12(%ebp)
	call	_Z12getOffsetRowi
	addl	$16, %esp
	movl	%eax, 16(%ebp)
	.loc 1 89 0
	movl	16(%ebp), %eax
	addl	$1, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$0
	call	_Z9getOffsetii
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	jmp	.L21
.L20:
	.loc 1 91 0
	movl	-12(%ebp), %edx
	movl	-20(%ebp), %eax
	addl	%eax, %edx
	movzbl	-28(%ebp), %eax
	movb	%al, (%edx)
	.loc 1 92 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%eax, %edx
	movzbl	-32(%ebp), %eax
	movb	%al, (%edx)
	.loc 1 93 0
	addl	$2, -12(%ebp)
.L21:
.LBB2:
	.loc 1 97 0
	cmpl	$3999, -12(%ebp)
	jle	.L22
.LBB3:
	.loc 1 100 0
	movl	$1, -16(%ebp)
.L24:
	.loc 1 100 0 is_stmt 0 discriminator 3
	cmpl	$24, -16(%ebp)
	jg	.L23
	.loc 1 103 0 is_stmt 1 discriminator 2
	subl	$8, %esp
	pushl	-16(%ebp)
	pushl	$0
	call	_Z9getOffsetii
	addl	$16, %esp
	addl	$753664, %eax
	.loc 1 102 0 discriminator 2
	movl	%eax, %ebx
	movl	-16(%ebp), %eax
	subl	$1, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$0
	call	_Z9getOffsetii
	addl	$16, %esp
	addl	$753664, %eax
	subl	$4, %esp
	pushl	$160
	pushl	%ebx
	pushl	%eax
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 100 0 discriminator 2
	addl	$1, -16(%ebp)
	jmp	.L24
.L23:
	.loc 1 108 0
	subl	$8, %esp
	pushl	$24
	pushl	$0
	call	_Z9getOffsetii
	addl	$16, %esp
	addl	$753664, %eax
	movl	%eax, -24(%ebp)
	.loc 1 109 0
	movl	$0, -16(%ebp)
.L26:
	.loc 1 109 0 is_stmt 0 discriminator 3
	cmpl	$159, -16(%ebp)
	jg	.L25
	.loc 1 111 0 is_stmt 1 discriminator 2
	movl	-16(%ebp), %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 109 0 discriminator 2
	addl	$1, -16(%ebp)
	jmp	.L26
.L25:
	.loc 1 114 0
	subl	$160, -12(%ebp)
.L22:
.LBE3:
.LBE2:
	.loc 1 116 0
	subl	$12, %esp
	pushl	-12(%ebp)
	call	_Z15setCursorOffseti
	addl	$16, %esp
	.loc 1 117 0
	movl	-12(%ebp), %eax
.L17:
	.loc 1 118 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	_Z9printCharciic, .-_Z9printCharciic
	.globl	_Z15getCursorOffsetv
	.type	_Z15getCursorOffsetv, @function
_Z15getCursorOffsetv:
.LFB5:
	.loc 1 121 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 126 0
	subl	$8, %esp
	pushl	$14
	pushl	$980
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 127 0
	subl	$12, %esp
	pushl	$981
	call	_Z10portByteInt
	addl	$16, %esp
	movzbl	%al, %eax
	sall	$8, %eax
	movl	%eax, -12(%ebp)
	.loc 1 128 0
	subl	$8, %esp
	pushl	$15
	pushl	$980
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 129 0
	subl	$12, %esp
	pushl	$981
	call	_Z10portByteInt
	addl	$16, %esp
	movzbl	%al, %eax
	addl	%eax, -12(%ebp)
	.loc 1 130 0
	movl	-12(%ebp), %eax
	addl	%eax, %eax
	.loc 1 131 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	_Z15getCursorOffsetv, .-_Z15getCursorOffsetv
	.globl	_Z15setCursorOffseti
	.type	_Z15setCursorOffseti, @function
_Z15setCursorOffseti:
.LFB6:
	.loc 1 134 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 136 0
	movl	8(%ebp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, 8(%ebp)
	.loc 1 137 0
	subl	$8, %esp
	pushl	$14
	pushl	$980
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 138 0
	movl	8(%ebp), %eax
	sarl	$8, %eax
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$981
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 139 0
	subl	$8, %esp
	pushl	$15
	pushl	$980
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 140 0
	movl	8(%ebp), %eax
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$981
	call	_Z11portByteOutth
	addl	$16, %esp
	.loc 1 141 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_Z15setCursorOffseti, .-_Z15setCursorOffseti
	.globl	_Z11clearScreenc
	.type	_Z11clearScreenc, @function
_Z11clearScreenc:
.LFB7:
	.loc 1 144 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movb	%al, -28(%ebp)
	.loc 1 145 0
	movl	$753664, -16(%ebp)
	.loc 1 146 0
	movl	$0, -12(%ebp)
.L34:
	.loc 1 148 0
	cmpl	$3999, -12(%ebp)
	ja	.L31
	.loc 1 150 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %edx
	addl	%edx, %eax
	movb	$32, (%eax)
	.loc 1 151 0
	cmpb	$0, -28(%ebp)
	je	.L32
	.loc 1 151 0 is_stmt 0 discriminator 1
	movzbl	-28(%ebp), %edx
	jmp	.L33
.L32:
	.loc 1 151 0 discriminator 2
	movl	$15, %edx
.L33:
	.loc 1 151 0 discriminator 4
	movl	-12(%ebp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, -12(%ebp)
	movl	-16(%ebp), %ecx
	addl	%ecx, %eax
	movb	%dl, (%eax)
	.loc 1 148 0 is_stmt 1 discriminator 4
	jmp	.L34
.L31:
	.loc 1 153 0
	subl	$12, %esp
	pushl	$0
	call	_Z15setCursorOffseti
	addl	$16, %esp
	.loc 1 154 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	_Z11clearScreenc, .-_Z11clearScreenc
	.globl	_Z9getOffsetii
	.type	_Z9getOffsetii, @function
_Z9getOffsetii:
.LFB8:
	.loc 1 157 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 157 0
	movl	12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	addl	%eax, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	_Z9getOffsetii, .-_Z9getOffsetii
	.globl	_Z12getOffsetRowi
	.type	_Z12getOffsetRowi, @function
_Z12getOffsetRowi:
.LFB9:
	.loc 1 158 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 158 0
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$6, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	_Z12getOffsetRowi, .-_Z12getOffsetRowi
	.globl	_Z12getOffsetColi
	.type	_Z12getOffsetColi, @function
_Z12getOffsetColi:
.LFB10:
	.loc 1 159 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 159 0
	pushl	8(%ebp)
	call	_Z12getOffsetRowi
	addl	$4, %esp
	imull	$-160, %eax, %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	_Z12getOffsetColi, .-_Z12getOffsetColi
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x32a
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
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
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
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x4
	.long	.LASF38
	.byte	0x1
	.byte	0xf
	.long	0x6e
	.uleb128 0x5
	.byte	0x3
	.long	g_textAttr
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x5
	.long	.LASF8
	.byte	0x1
	.byte	0x9f
	.long	.LASF10
	.long	0x3a
	.long	.LFB10
	.long	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0xa1
	.uleb128 0x6
	.long	.LASF12
	.byte	0x1
	.byte	0x9f
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.long	.LASF9
	.byte	0x1
	.byte	0x9e
	.long	.LASF11
	.long	0x3a
	.long	.LFB9
	.long	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0xcd
	.uleb128 0x6
	.long	.LASF12
	.byte	0x1
	.byte	0x9e
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x9d
	.long	.LASF14
	.long	0x3a
	.long	.LFB8
	.long	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x107
	.uleb128 0x8
	.string	"col"
	.byte	0x1
	.byte	0x9d
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x8
	.string	"row"
	.byte	0x1
	.byte	0x9d
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x8f
	.long	.LASF19
	.long	.LFB7
	.long	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x149
	.uleb128 0x6
	.long	.LASF15
	.byte	0x1
	.byte	0x8f
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xa
	.long	.LASF16
	.byte	0x1
	.byte	0x91
	.long	0x149
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.string	"j"
	.byte	0x1
	.byte	0x92
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x6e
	.uleb128 0x9
	.long	.LASF18
	.byte	0x1
	.byte	0x85
	.long	.LASF20
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x177
	.uleb128 0x6
	.long	.LASF12
	.byte	0x1
	.byte	0x85
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.long	.LASF21
	.byte	0x1
	.byte	0x78
	.long	.LASF22
	.long	0x3a
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a3
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x7f
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x5
	.long	.LASF23
	.byte	0x1
	.byte	0x45
	.long	.LASF24
	.long	0x3a
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x237
	.uleb128 0x8
	.string	"c"
	.byte	0x1
	.byte	0x45
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x8
	.string	"col"
	.byte	0x1
	.byte	0x45
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x8
	.string	"row"
	.byte	0x1
	.byte	0x45
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x6
	.long	.LASF15
	.byte	0x1
	.byte	0x45
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xa
	.long	.LASF16
	.byte	0x1
	.byte	0x47
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x52
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xd
	.long	.LBB3
	.long	.LBE3-.LBB3
	.uleb128 0xb
	.string	"i"
	.byte	0x1
	.byte	0x63
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.long	.LASF25
	.byte	0x1
	.byte	0x6c
	.long	0x149
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x4f
	.uleb128 0x9
	.long	.LASF26
	.byte	0x1
	.byte	0x3c
	.long	.LASF27
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x265
	.uleb128 0x6
	.long	.LASF28
	.byte	0x1
	.byte	0x3c
	.long	0x149
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x9
	.long	.LASF29
	.byte	0x1
	.byte	0x31
	.long	.LASF30
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x28d
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x33
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x9
	.long	.LASF31
	.byte	0x1
	.byte	0x1c
	.long	.LASF32
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x2f9
	.uleb128 0x6
	.long	.LASF28
	.byte	0x1
	.byte	0x1c
	.long	0x149
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x8
	.string	"col"
	.byte	0x1
	.byte	0x1c
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x8
	.string	"row"
	.byte	0x1
	.byte	0x1c
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x6
	.long	.LASF15
	.byte	0x1
	.byte	0x1c
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x1e
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.string	"i"
	.byte	0x1
	.byte	0x28
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xe
	.long	.LASF33
	.byte	0x1
	.byte	0x15
	.long	.LASF34
	.long	0x6e
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.long	.LASF15
	.byte	0x1
	.byte	0x15
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xb
	.string	"a"
	.byte	0x1
	.byte	0x17
	.long	0x6e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -9
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x8
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
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
	.uleb128 0x49
	.uleb128 0x13
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
.LASF28:
	.string	"message"
.LASF21:
	.string	"getCursorOffset"
.LASF34:
	.string	"_Z15defaultTextAttrc"
.LASF22:
	.string	"_Z15getCursorOffsetv"
.LASF11:
	.string	"_Z12getOffsetRowi"
.LASF10:
	.string	"_Z12getOffsetColi"
.LASF27:
	.string	"_Z6kprintPc"
.LASF8:
	.string	"getOffsetCol"
.LASF23:
	.string	"printChar"
.LASF38:
	.string	"g_textAttr"
.LASF5:
	.string	"unsigned char"
.LASF25:
	.string	"last_line"
.LASF13:
	.string	"getOffset"
.LASF15:
	.string	"attr"
.LASF33:
	.string	"defaultTextAttr"
.LASF3:
	.string	"short unsigned int"
.LASF19:
	.string	"_Z11clearScreenc"
.LASF17:
	.string	"clearScreen"
.LASF9:
	.string	"getOffsetRow"
.LASF36:
	.string	"drivers/screen.cpp"
.LASF14:
	.string	"_Z9getOffsetii"
.LASF29:
	.string	"printBackspace"
.LASF2:
	.string	"unsigned int"
.LASF31:
	.string	"kprintAt"
.LASF0:
	.string	"long long unsigned int"
.LASF26:
	.string	"kprint"
.LASF1:
	.string	"long long int"
.LASF30:
	.string	"_Z14printBackspacev"
.LASF7:
	.string	"char"
.LASF35:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF20:
	.string	"_Z15setCursorOffseti"
.LASF12:
	.string	"offset"
.LASF4:
	.string	"short int"
.LASF24:
	.string	"_Z9printCharciic"
.LASF37:
	.string	"/home/alexis/src/hydrogen"
.LASF18:
	.string	"setCursorOffset"
.LASF16:
	.string	"vidmem"
.LASF6:
	.string	"signed char"
.LASF32:
	.string	"_Z8kprintAtPciic"
	.ident	"GCC: (GNU) 7.2.0"
