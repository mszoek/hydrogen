	.file	"kstring.cpp"
	.text
.Ltext0:
	.globl	_Z6strlenPc
	.type	_Z6strlenPc, @function
_Z6strlenPc:
.LFB0:
	.file 1 "kernel/kstring.cpp"
	.loc 1 6 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 7 0
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
.L3:
	.loc 1 8 0 discriminator 2
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L2
	.loc 1 8 0 is_stmt 0 discriminator 1
	addl	$1, -4(%ebp)
	jmp	.L3
.L2:
	.loc 1 9 0 is_stmt 1
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	.loc 1 10 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z6strlenPc, .-_Z6strlenPc
	.globl	_Z6strcmpPcS_
	.type	_Z6strcmpPcS_, @function
_Z6strcmpPcS_:
.LFB1:
	.loc 1 13 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 3, -12
	.loc 1 14 0
	pushl	8(%ebp)
	call	_Z6strlenPc
	addl	$4, %esp
	movl	%eax, %ebx
	pushl	12(%ebp)
	call	_Z6strlenPc
	addl	$4, %esp
	cmpl	%eax, %ebx
	setne	%al
	testb	%al, %al
	je	.L6
	.loc 1 14 0 is_stmt 0 discriminator 1
	movl	$1, %eax
	jmp	.L7
.L6:
	.loc 1 15 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	.loc 1 16 0
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
.L11:
	.loc 1 17 0
	movl	-8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L8
	.loc 1 17 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L8
	.loc 1 19 0 is_stmt 1
	movl	-8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	jge	.L9
	.loc 1 21 0
	movl	$-1, %eax
	jmp	.L7
.L9:
	.loc 1 23 0
	movl	-8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	jle	.L10
	.loc 1 25 0
	movl	$1, %eax
	jmp	.L7
.L10:
	.loc 1 27 0
	addl	$1, -8(%ebp)
	.loc 1 28 0
	addl	$1, -12(%ebp)
	.loc 1 17 0
	jmp	.L11
.L8:
	.loc 1 30 0
	movl	$0, %eax
.L7:
	.loc 1 31 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z6strcmpPcS_, .-_Z6strcmpPcS_
	.globl	_Z4atoiPc
	.type	_Z4atoiPc, @function
_Z4atoiPc:
.LFB2:
	.loc 1 34 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 35 0
	movl	$0, -4(%ebp)
.LBB2:
	.loc 1 39 0
	movl	$0, -8(%ebp)
.L14:
	.loc 1 39 0 is_stmt 0 discriminator 3
	movl	-8(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L13
	.loc 1 40 0 is_stmt 1 discriminator 2
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %ecx
	movl	-8(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	addl	%ecx, %eax
	subl	$48, %eax
	movl	%eax, -4(%ebp)
	.loc 1 39 0 discriminator 2
	addl	$1, -8(%ebp)
	jmp	.L14
.L13:
.LBE2:
	.loc 1 43 0
	movl	-4(%ebp), %eax
	.loc 1 44 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z4atoiPc, .-_Z4atoiPc
	.globl	_Z7reversePc
	.type	_Z7reversePc, @function
_Z7reversePc:
.LFB3:
	.loc 1 48 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 50 0
	movl	$0, -4(%ebp)
	pushl	8(%ebp)
	call	_Z6strlenPc
	addl	$4, %esp
	subl	$1, %eax
	movl	%eax, -8(%ebp)
.L18:
	.loc 1 50 0 is_stmt 0 discriminator 3
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jge	.L19
	.loc 1 52 0 is_stmt 1 discriminator 2
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	.loc 1 53 0 discriminator 2
	movl	-8(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	-4(%ebp), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movzbl	(%eax), %eax
	movb	%al, (%edx)
	.loc 1 54 0 discriminator 2
	movl	-8(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	-12(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 50 0 discriminator 2
	addl	$1, -4(%ebp)
	subl	$1, -8(%ebp)
	jmp	.L18
.L19:
	.loc 1 56 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	_Z7reversePc, .-_Z7reversePc
	.globl	_Z6appendPcc
	.type	_Z6appendPcc, @function
_Z6appendPcc:
.LFB4:
	.loc 1 59 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	12(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 60 0
	pushl	8(%ebp)
	call	_Z6strlenPc
	addl	$4, %esp
	movl	%eax, -4(%ebp)
	.loc 1 61 0
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movzbl	-20(%ebp), %eax
	movb	%al, (%edx)
	.loc 1 62 0
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 63 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	_Z6appendPcc, .-_Z6appendPcc
	.globl	_Z9backspacePc
	.type	_Z9backspacePc, @function
_Z9backspacePc:
.LFB5:
	.loc 1 66 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 67 0
	pushl	8(%ebp)
	call	_Z6strlenPc
	addl	$4, %esp
	movl	%eax, -4(%ebp)
	.loc 1 68 0
	movl	-4(%ebp), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 69 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	_Z9backspacePc, .-_Z9backspacePc
	.globl	_Z4itoaiPc
	.type	_Z4itoaiPc, @function
_Z4itoaiPc:
.LFB6:
	.loc 1 72 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 74 0
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	shrl	$31, %eax
	testb	%al, %al
	je	.L23
	.loc 1 74 0 is_stmt 0 discriminator 1
	negl	8(%ebp)
.L23:
	.loc 1 75 0 is_stmt 1
	movl	$0, -4(%ebp)
.L25:
	.loc 1 78 0
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, %eax
	leal	48(%eax), %ecx
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	%ecx, %edx
	movb	%dl, (%eax)
	.loc 1 79 0
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 8(%ebp)
	cmpl	$0, 8(%ebp)
	setg	%al
	testb	%al, %al
	je	.L24
	.loc 1 76 0
	jmp	.L25
.L24:
	.loc 1 81 0
	cmpl	$0, -8(%ebp)
	jns	.L26
	.loc 1 81 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movb	$45, (%eax)
.L26:
	.loc 1 82 0 is_stmt 1
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 84 0
	pushl	12(%ebp)
	call	_Z7reversePc
	addl	$4, %esp
	.loc 1 85 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_Z4itoaiPc, .-_Z4itoaiPc
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x214
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF16
	.byte	0x4
	.long	.LASF17
	.long	.LASF18
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF2
	.byte	0x1
	.byte	0x47
	.long	.LASF4
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x73
	.uleb128 0x3
	.string	"n"
	.byte	0x1
	.byte	0x47
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x3
	.string	"str"
	.byte	0x1
	.byte	0x47
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x4
	.string	"i"
	.byte	0x1
	.byte	0x49
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x5
	.long	.LASF0
	.byte	0x1
	.byte	0x49
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x7
	.byte	0x4
	.long	0x80
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.long	.LASF1
	.uleb128 0x2
	.long	.LASF3
	.byte	0x1
	.byte	0x41
	.long	.LASF5
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0xbb
	.uleb128 0x3
	.string	"s"
	.byte	0x1
	.byte	0x41
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x4
	.string	"len"
	.byte	0x1
	.byte	0x43
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2
	.long	.LASF6
	.byte	0x1
	.byte	0x3a
	.long	.LASF7
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0xfb
	.uleb128 0x3
	.string	"s"
	.byte	0x1
	.byte	0x3a
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x3
	.string	"n"
	.byte	0x1
	.byte	0x3a
	.long	0x80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x4
	.string	"len"
	.byte	0x1
	.byte	0x3c
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2
	.long	.LASF8
	.byte	0x1
	.byte	0x2f
	.long	.LASF9
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x147
	.uleb128 0x3
	.string	"str"
	.byte	0x1
	.byte	0x2f
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x4
	.string	"c"
	.byte	0x1
	.byte	0x31
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x4
	.string	"i"
	.byte	0x1
	.byte	0x31
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x4
	.string	"j"
	.byte	0x1
	.byte	0x31
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x9
	.long	.LASF10
	.byte	0x1
	.byte	0x21
	.long	.LASF12
	.long	0x73
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x197
	.uleb128 0x3
	.string	"str"
	.byte	0x1
	.byte	0x21
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x4
	.string	"res"
	.byte	0x1
	.byte	0x23
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xa
	.long	.LBB2
	.long	.LBE2-.LBB2
	.uleb128 0x4
	.string	"i"
	.byte	0x1
	.byte	0x27
	.long	0x73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	.LASF11
	.byte	0x1
	.byte	0xc
	.long	.LASF13
	.long	0x73
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x1e5
	.uleb128 0x3
	.string	"a"
	.byte	0x1
	.byte	0xc
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x3
	.string	"b"
	.byte	0x1
	.byte	0xc
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x4
	.string	"p"
	.byte	0x1
	.byte	0xf
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x4
	.string	"q"
	.byte	0x1
	.byte	0x10
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xc
	.long	.LASF14
	.byte	0x1
	.byte	0x5
	.long	.LASF15
	.long	0x73
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3
	.string	"s"
	.byte	0x1
	.byte	0x5
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x4
	.string	"p"
	.byte	0x1
	.byte	0x7
	.long	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
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
	.uleb128 0x3
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0xa
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
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
.LASF14:
	.string	"strlen"
.LASF9:
	.string	"_Z7reversePc"
.LASF15:
	.string	"_Z6strlenPc"
.LASF13:
	.string	"_Z6strcmpPcS_"
.LASF18:
	.string	"/home/alexis/src/hydrogen"
.LASF0:
	.string	"sign"
.LASF16:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF17:
	.string	"kernel/kstring.cpp"
.LASF11:
	.string	"strcmp"
.LASF8:
	.string	"reverse"
.LASF4:
	.string	"_Z4itoaiPc"
.LASF6:
	.string	"append"
.LASF5:
	.string	"_Z9backspacePc"
.LASF10:
	.string	"atoi"
.LASF7:
	.string	"_Z6appendPcc"
.LASF12:
	.string	"_Z4atoiPc"
.LASF3:
	.string	"backspace"
.LASF2:
	.string	"itoa"
.LASF1:
	.string	"char"
	.ident	"GCC: (GNU) 7.2.0"
