	.file	"idt.cpp"
	.text
.Ltext0:
	.globl	idt
	.section	.bss
	.align 32
	.type	idt, @object
	.size	idt, 2048
idt:
	.zero	2048
	.globl	idt_reg
	.align 4
	.type	idt_reg, @object
	.size	idt_reg, 6
idt_reg:
	.zero	6
	.text
	.globl	_Z10setIDTGateij
	.type	_Z10setIDTGateij, @function
_Z10setIDTGateij:
.LFB0:
	.file 1 "hw/idt.cpp"
	.loc 1 8 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 9 0
	movl	12(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, idt(,%eax,8)
	.loc 1 10 0
	movl	8(%ebp), %eax
	movw	$8, idt+2(,%eax,8)
	.loc 1 11 0
	movl	8(%ebp), %eax
	movb	$0, idt+4(,%eax,8)
	.loc 1 12 0
	movl	8(%ebp), %eax
	movb	$-114, idt+5(,%eax,8)
	.loc 1 13 0
	movl	12(%ebp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, idt+6(,%eax,8)
	.loc 1 14 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_Z10setIDTGateij, .-_Z10setIDTGateij
	.globl	_Z6setIDTv
	.type	_Z6setIDTv, @function
_Z6setIDTv:
.LFB1:
	.loc 1 17 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 18 0
	movl	$idt, %eax
	movl	%eax, idt_reg+2
	.loc 1 19 0
	movw	$2047, idt_reg
	.loc 1 21 0
	movl	$idt_reg, %eax
/APP
/  21 "hw/idt.cpp" 1
	lidtl (%eax)
/  0 "" 2
	.loc 1 22 0
/NO_APP
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z6setIDTv, .-_Z6setIDTv
.Letext0:
	.file 2 "includes/hw/types.h"
	.file 3 "includes/hw/idt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x18b
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF23
	.byte	0x4
	.long	.LASF24
	.long	.LASF25
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
	.long	0x119
	.byte	0x1
	.byte	0x4
	.uleb128 0x5
	.byte	0x3
	.long	idt
	.uleb128 0xc
	.long	0x124
	.byte	0x1
	.byte	0x5
	.uleb128 0x5
	.byte	0x3
	.long	idt_reg
	.uleb128 0xd
	.long	.LASF26
	.byte	0x1
	.byte	0x10
	.long	.LASF27
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.long	.LASF28
	.byte	0x1
	.byte	0x7
	.long	.LASF29
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xf
	.string	"n"
	.byte	0x1
	.byte	0x7
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x10
	.long	.LASF22
	.byte	0x1
	.byte	0x7
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
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
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0x2117
	.uleb128 0x19
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
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
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
.LASF1:
	.string	"long long int"
.LASF28:
	.string	"setIDTGate"
.LASF2:
	.string	"unsigned int"
.LASF7:
	.string	"UInt8"
.LASF15:
	.string	"10idt_gate_t"
.LASF12:
	.string	"flags"
.LASF4:
	.string	"UInt16"
.LASF22:
	.string	"handler"
.LASF17:
	.string	"limit"
.LASF13:
	.string	"high_offset"
.LASF3:
	.string	"UInt32"
.LASF0:
	.string	"long long unsigned int"
.LASF25:
	.string	"/home/alexis/src/hydrogen"
.LASF23:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF18:
	.string	"base"
.LASF11:
	.string	"always0"
.LASF29:
	.string	"_Z10setIDTGateij"
.LASF8:
	.string	"unsigned char"
.LASF19:
	.string	"idt_register_t"
.LASF10:
	.string	"low_offset"
.LASF20:
	.string	"long unsigned int"
.LASF14:
	.string	"idt_gate_t"
.LASF5:
	.string	"short unsigned int"
.LASF9:
	.string	"signed char"
.LASF16:
	.string	"14idt_register_t"
.LASF24:
	.string	"hw/idt.cpp"
.LASF27:
	.string	"_Z6setIDTv"
.LASF26:
	.string	"setIDT"
.LASF6:
	.string	"short int"
.LASF21:
	.string	"idt_reg"
	.ident	"GCC: (GNU) 7.2.0"
