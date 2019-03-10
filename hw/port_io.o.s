	.file	"port_io.cpp"
	.text
.Ltext0:
	.globl	_Z10portByteInt
	.type	_Z10portByteInt, @function
_Z10portByteInt:
.LFB0:
	.file 1 "hw/port_io.cpp"
	.loc 1 5 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	8(%ebp), %eax
	movw	%ax, -20(%ebp)
	.loc 1 7 0
	movzwl	-20(%ebp), %eax
	movl	%eax, %edx
/APP
/  7 "hw/port_io.cpp" 1
	in %dx, %al
/  0 "" 2
/NO_APP
	movb	%al, -1(%ebp)
	.loc 1 8 0
	movzbl	-1(%ebp), %eax
	.loc 1 9 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z10portByteInt, .-_Z10portByteInt
	.globl	_Z11portByteOutth
	.type	_Z11portByteOutth, @function
_Z11portByteOutth:
.LFB1:
	.loc 1 12 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movw	%dx, -4(%ebp)
	movb	%al, -8(%ebp)
	.loc 1 13 0
	movzbl	-8(%ebp), %eax
	movzwl	-4(%ebp), %edx
/APP
/  13 "hw/port_io.cpp" 1
	out %al, %dx
/  0 "" 2
	.loc 1 14 0
/NO_APP
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z11portByteOutth, .-_Z11portByteOutth
	.globl	_Z10portWordInt
	.type	_Z10portWordInt, @function
_Z10portWordInt:
.LFB2:
	.loc 1 17 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	8(%ebp), %eax
	movw	%ax, -20(%ebp)
	.loc 1 19 0
	movzwl	-20(%ebp), %eax
	movl	%eax, %edx
/APP
/  19 "hw/port_io.cpp" 1
	in %dx, %ax
/  0 "" 2
/NO_APP
	movw	%ax, -2(%ebp)
	.loc 1 20 0
	movzwl	-2(%ebp), %eax
	.loc 1 21 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z10portWordInt, .-_Z10portWordInt
	.globl	_Z11portWordOuttt
	.type	_Z11portWordOuttt, @function
_Z11portWordOuttt:
.LFB3:
	.loc 1 24 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movw	%dx, -4(%ebp)
	movw	%ax, -8(%ebp)
	.loc 1 25 0
	movzwl	-8(%ebp), %eax
	movzwl	-4(%ebp), %edx
/APP
/  25 "hw/port_io.cpp" 1
	out %ax, %dx
/  0 "" 2
	.loc 1 26 0
/NO_APP
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	_Z11portWordOuttt, .-_Z11portWordOuttt
.Letext0:
	.file 2 "includes/hw/types.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x14c
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF18
	.byte	0x4
	.long	.LASF19
	.long	.LASF20
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
	.uleb128 0x4
	.long	.LASF5
	.byte	0x2
	.byte	0xa
	.long	0x4c
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF4
	.uleb128 0x4
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
	.long	.LASF11
	.byte	0x1
	.byte	0x17
	.long	.LASF13
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0xa9
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0x17
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x6
	.long	.LASF10
	.byte	0x1
	.byte	0x17
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x7
	.long	.LASF21
	.byte	0x1
	.byte	0x10
	.long	.LASF22
	.long	0x41
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0xe3
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0x10
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x8
	.long	.LASF17
	.byte	0x1
	.byte	0x12
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -10
	.byte	0
	.uleb128 0x5
	.long	.LASF12
	.byte	0x1
	.byte	0xb
	.long	.LASF14
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x119
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0xb
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x6
	.long	.LASF10
	.byte	0x1
	.byte	0xb
	.long	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x9
	.long	.LASF15
	.byte	0x1
	.byte	0x4
	.long	.LASF16
	.long	0x5a
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0x4
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x8
	.long	.LASF17
	.byte	0x1
	.byte	0x6
	.long	0x5a
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
.LASF2:
	.string	"unsigned int"
.LASF19:
	.string	"hw/port_io.cpp"
.LASF5:
	.string	"UInt16"
.LASF6:
	.string	"UInt8"
.LASF16:
	.string	"_Z10portByteInt"
.LASF0:
	.string	"long long unsigned int"
.LASF20:
	.string	"/home/alexis/src/hydrogen"
.LASF18:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF14:
	.string	"_Z11portByteOutth"
.LASF7:
	.string	"unsigned char"
.LASF10:
	.string	"data"
.LASF17:
	.string	"result"
.LASF22:
	.string	"_Z10portWordInt"
.LASF9:
	.string	"port"
.LASF15:
	.string	"portByteIn"
.LASF3:
	.string	"short unsigned int"
.LASF8:
	.string	"signed char"
.LASF13:
	.string	"_Z11portWordOuttt"
.LASF11:
	.string	"portWordOut"
.LASF4:
	.string	"short int"
.LASF12:
	.string	"portByteOut"
.LASF21:
	.string	"portWordIn"
	.ident	"GCC: (GNU) 7.2.0"
