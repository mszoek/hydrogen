	.file	"shell.cpp"
	.text
.Ltext0:
	.section	.rodata
	.align 32
	.type	_ZL16scanCodesToASCII, @object
	.size	_ZL16scanCodesToASCII, 89
_ZL16scanCodesToASCII:
	.byte	-1
	.byte	27
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	48
	.byte	45
	.byte	61
	.byte	8
	.byte	9
	.byte	113
	.byte	119
	.byte	101
	.byte	114
	.byte	116
	.byte	121
	.byte	117
	.byte	105
	.byte	111
	.byte	112
	.byte	91
	.byte	93
	.byte	13
	.byte	-1
	.byte	97
	.byte	115
	.byte	100
	.byte	102
	.byte	103
	.byte	104
	.byte	106
	.byte	107
	.byte	108
	.byte	59
	.byte	39
	.byte	96
	.byte	-1
	.byte	92
	.byte	122
	.byte	120
	.byte	99
	.byte	118
	.byte	98
	.byte	110
	.byte	109
	.byte	44
	.byte	46
	.byte	47
	.byte	-1
	.byte	42
	.byte	-1
	.byte	32
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-1
	.byte	-1
	.byte	55
	.byte	56
	.byte	57
	.byte	45
	.byte	52
	.byte	53
	.byte	54
	.byte	43
	.byte	49
	.byte	50
	.byte	51
	.byte	48
	.byte	46
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.globl	PROMPT
.LC0:
	.string	"H2> "
	.data
	.align 4
	.type	PROMPT, @object
	.size	PROMPT, 4
PROMPT:
	.long	.LC0
	.globl	shellBuffer
	.section	.bss
	.align 32
	.type	shellBuffer, @object
	.size	shellBuffer, 1024
shellBuffer:
	.zero	1024
	.globl	shellBufferPos
	.align 4
	.type	shellBufferPos, @object
	.size	shellBufferPos, 4
shellBufferPos:
	.zero	4
	.text
	.globl	_Z10shellStartv
	.type	_Z10shellStartv, @function
_Z10shellStartv:
.LFB0:
	.file 1 "kernel/shell.cpp"
	.loc 1 25 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 26 0
	subl	$4, %esp
	pushl	$1024
	pushl	$0
	pushl	$shellBuffer
	call	_Z6memsetPcci
	addl	$16, %esp
	.loc 1 27 0
	movl	$0, shellBufferPos
	.loc 1 28 0
	movl	PROMPT, %eax
	subl	$12, %esp
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 29 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z10shellStartv, .-_Z10shellStartv
	.section	.rodata
.LC1:
	.string	"exit"
.LC2:
	.string	"kk, kthxbye!\n"
.LC3:
	.string	"hello"
.LC4:
	.string	"'ello gorgeous!\n"
.LC5:
	.string	"Invalid command\n"
	.text
	.globl	_Z16shellExecCommandv
	.type	_Z16shellExecCommandv, @function
_Z16shellExecCommandv:
.LFB1:
	.loc 1 32 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 33 0
	subl	$12, %esp
	pushl	$shellBuffer
	call	_Z6strlenPc
	addl	$16, %esp
	testl	%eax, %eax
	setle	%al
	testb	%al, %al
	jne	.L7
	.loc 1 35 0
	subl	$8, %esp
	pushl	$.LC1
	pushl	$shellBuffer
	call	_Z6strcmpPcS_
	addl	$16, %esp
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	.L5
	.loc 1 37 0
	subl	$12, %esp
	pushl	$.LC2
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 38 0
/APP
/  38 "kernel/shell.cpp" 1
	cli
/  0 "" 2
	.loc 1 39 0
/  39 "kernel/shell.cpp" 1
	hlt
/  0 "" 2
/NO_APP
.L5:
	.loc 1 41 0
	subl	$8, %esp
	pushl	$.LC3
	pushl	$shellBuffer
	call	_Z6strcmpPcS_
	addl	$16, %esp
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	.L6
	.loc 1 43 0
	subl	$12, %esp
	pushl	$.LC4
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 44 0
	jmp	.L2
.L6:
	.loc 1 47 0
	pushl	$12
	pushl	$-1
	pushl	$-1
	pushl	$.LC5
	call	_Z8kprintAtPciic
	addl	$16, %esp
	jmp	.L2
.L7:
	.loc 1 33 0
	nop
.L2:
	.loc 1 48 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z16shellExecCommandv, .-_Z16shellExecCommandv
	.section	.rodata
.LC6:
	.string	"\n"
	.text
	.globl	_Z15shellCheckInputv
	.type	_Z15shellCheckInputv, @function
_Z15shellCheckInputv:
.LFB2:
	.loc 1 51 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$1064, %esp
	.loc 1 53 0
	movl	$0, -12(%ebp)
	.loc 1 55 0
	subl	$8, %esp
	pushl	$1023
	leal	-1048(%ebp), %eax
	pushl	%eax
	call	_Z17getKeyboardBufferPct
	addl	$16, %esp
	movzwl	%ax, %eax
	movl	%eax, -24(%ebp)
.LBB2:
	.loc 1 57 0
	movl	$0, -16(%ebp)
.L18:
	.loc 1 57 0 is_stmt 0 discriminator 1
	movl	-16(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jge	.L8
.LBB3:
	.loc 1 59 0 is_stmt 1
	leal	-1048(%ebp), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movb	%al, -17(%ebp)
	.loc 1 60 0
	cmpb	$0, -17(%ebp)
	jns	.L10
	.loc 1 62 0
	movl	$1, -12(%ebp)
	.loc 1 63 0
	andb	$127, -17(%ebp)
.L10:
.LBB4:
	.loc 1 66 0
	cmpl	$0, -12(%ebp)
	je	.L11
.LBB5:
	.loc 1 68 0
	cmpb	$28, -17(%ebp)
	jne	.L12
	.loc 1 70 0
	subl	$12, %esp
	pushl	$.LC6
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 71 0
	movl	shellBufferPos, %eax
	leal	1(%eax), %edx
	movl	%edx, shellBufferPos
	movb	$0, shellBuffer(%eax)
	.loc 1 72 0
	call	_Z16shellExecCommandv
	.loc 1 73 0
	movl	$0, shellBufferPos
	.loc 1 74 0
	movb	$0, shellBuffer
	.loc 1 75 0
	movl	PROMPT, %eax
	subl	$12, %esp
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 76 0
	jmp	.L8
.L12:
	.loc 1 78 0
	cmpb	$14, -17(%ebp)
	jne	.L14
	.loc 1 80 0
	movl	shellBufferPos, %eax
	testl	%eax, %eax
	je	.L19
	.loc 1 82 0
	movl	shellBufferPos, %eax
	subl	$1, %eax
	movl	%eax, shellBufferPos
	movl	shellBufferPos, %eax
	movb	$0, shellBuffer(%eax)
	.loc 1 83 0
	call	_Z14printBackspacev
	.loc 1 85 0
	jmp	.L19
.L14:
	.loc 1 88 0
	movl	shellBufferPos, %eax
	cmpl	$1022, %eax
	ja	.L20
	.loc 1 94 0
	movsbl	-17(%ebp), %eax
	movzbl	_ZL16scanCodesToASCII(%eax), %eax
	movb	%al, -17(%ebp)
	.loc 1 95 0
	movl	shellBufferPos, %eax
	leal	1(%eax), %edx
	movl	%edx, shellBufferPos
	movzbl	-17(%ebp), %edx
	movb	%dl, shellBuffer(%eax)
	.loc 1 97 0
	movzbl	-17(%ebp), %eax
	movb	%al, -1050(%ebp)
	.loc 1 98 0
	movb	$0, -1049(%ebp)
	.loc 1 99 0
	subl	$12, %esp
	leal	-1050(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
.L11:
.LBE5:
.LBE4:
.LBE3:
	.loc 1 57 0 discriminator 2
	addl	$1, -16(%ebp)
	jmp	.L18
.L19:
.LBB8:
.LBB7:
.LBB6:
	.loc 1 85 0
	nop
	jmp	.L8
.L20:
	.loc 1 90 0
	nop
.L8:
.LBE6:
.LBE7:
.LBE8:
.LBE2:
	.loc 1 102 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z15shellCheckInputv, .-_Z15shellCheckInputv
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1a6
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF20
	.byte	0x4
	.long	.LASF21
	.long	.LASF22
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
	.long	0x80
	.long	0x6d
	.uleb128 0x5
	.long	0x72
	.byte	0x58
	.byte	0
	.uleb128 0x6
	.long	0x5d
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF8
	.uleb128 0x6
	.long	0x79
	.uleb128 0x7
	.long	.LASF12
	.byte	0x1
	.byte	0x9
	.long	0x6d
	.uleb128 0x5
	.byte	0x3
	.long	_ZL16scanCodesToASCII
	.uleb128 0x8
	.long	.LASF9
	.byte	0x1
	.byte	0x14
	.long	0xa7
	.uleb128 0x5
	.byte	0x3
	.long	PROMPT
	.uleb128 0x9
	.byte	0x4
	.long	0x79
	.uleb128 0x4
	.long	0x79
	.long	0xbe
	.uleb128 0xa
	.long	0x72
	.value	0x3ff
	.byte	0
	.uleb128 0x8
	.long	.LASF10
	.byte	0x1
	.byte	0x15
	.long	0xad
	.uleb128 0x5
	.byte	0x3
	.long	shellBuffer
	.uleb128 0x8
	.long	.LASF11
	.byte	0x1
	.byte	0x16
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	shellBufferPos
	.uleb128 0xb
	.long	.LASF23
	.byte	0x1
	.byte	0x32
	.long	.LASF24
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x16f
	.uleb128 0xc
	.long	.LASF15
	.byte	0x1
	.byte	0x34
	.long	0x79
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x35
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xd
	.string	"buf"
	.byte	0x1
	.byte	0x36
	.long	0xad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -1056
	.uleb128 0x7
	.long	.LASF14
	.byte	0x1
	.byte	0x37
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xe
	.long	.LBB2
	.long	.LBE2-.LBB2
	.uleb128 0xd
	.string	"i"
	.byte	0x1
	.byte	0x39
	.long	0x3a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xf
	.long	.Ldebug_ranges0+0
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x3b
	.long	0x79
	.uleb128 0x2
	.byte	0x91
	.sleb128 -25
	.uleb128 0xf
	.long	.Ldebug_ranges0+0x18
	.uleb128 0xd
	.string	"key"
	.byte	0x1
	.byte	0x60
	.long	0x16f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -1058
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4
	.long	0x79
	.long	0x17f
	.uleb128 0x5
	.long	0x72
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF16
	.byte	0x1
	.byte	0x1f
	.long	.LASF18
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x10
	.long	.LASF17
	.byte	0x1
	.byte	0x18
	.long	.LASF19
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LBB3-.Ltext0
	.long	.LBE3-.Ltext0
	.long	.LBB8-.Ltext0
	.long	.LBE8-.Ltext0
	.long	0
	.long	0
	.long	.LBB5-.Ltext0
	.long	.LBE5-.Ltext0
	.long	.LBB6-.Ltext0
	.long	.LBE6-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF13:
	.string	"keyUp"
.LASF16:
	.string	"shellExecCommand"
.LASF5:
	.string	"unsigned char"
.LASF10:
	.string	"shellBuffer"
.LASF7:
	.string	"long unsigned int"
.LASF3:
	.string	"short unsigned int"
.LASF11:
	.string	"shellBufferPos"
.LASF21:
	.string	"kernel/shell.cpp"
.LASF15:
	.string	"code"
.LASF2:
	.string	"unsigned int"
.LASF0:
	.string	"long long unsigned int"
.LASF18:
	.string	"_Z16shellExecCommandv"
.LASF1:
	.string	"long long int"
.LASF8:
	.string	"char"
.LASF24:
	.string	"_Z15shellCheckInputv"
.LASF20:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF9:
	.string	"PROMPT"
.LASF4:
	.string	"short int"
.LASF12:
	.string	"scanCodesToASCII"
.LASF23:
	.string	"shellCheckInput"
.LASF22:
	.string	"/home/alexis/src/hydrogen"
.LASF17:
	.string	"shellStart"
.LASF6:
	.string	"signed char"
.LASF14:
	.string	"length"
.LASF19:
	.string	"_Z10shellStartv"
	.ident	"GCC: (GNU) 7.2.0"
