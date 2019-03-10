	.file	"keyboard.cpp"
	.text
.Ltext0:
	.local	_ZL9keyBuffer
	.comm	_ZL9keyBuffer,1024,32
	.local	_ZL12keyBufferPos
	.comm	_ZL12keyBufferPos,4,4
	.type	_ZL16keyboardCallback11registers_t, @function
_ZL16keyboardCallback11registers_t:
.LFB0:
	.file 1 "drivers/keyboard.cpp"
	.loc 1 12 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 13 0
	subl	$12, %esp
	pushl	$96
	call	_Z10portByteInt
	addl	$16, %esp
	movb	%al, -9(%ebp)
	.loc 1 14 0
	movzbl	-9(%ebp), %eax
	andl	$127, %eax
	movb	%al, -10(%ebp)
	.loc 1 17 0
	cmpb	$88, -10(%ebp)
	ja	.L4
	.loc 1 22 0
	movl	_ZL12keyBufferPos, %eax
	movzbl	-9(%ebp), %edx
	movb	%dl, _ZL9keyBuffer(%eax)
	.loc 1 23 0
	movl	_ZL12keyBufferPos, %eax
	addl	$1, %eax
	movl	%eax, _ZL12keyBufferPos
	.loc 1 24 0
	movl	_ZL12keyBufferPos, %eax
	cmpl	$1023, %eax
	jle	.L1
	.loc 1 26 0
	movl	$1023, _ZL12keyBufferPos
	jmp	.L1
.L4:
	.loc 1 19 0
	nop
.L1:
	.loc 1 29 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_ZL16keyboardCallback11registers_t, .-_ZL16keyboardCallback11registers_t
	.globl	_Z12initKeyboardv
	.type	_Z12initKeyboardv, @function
_Z12initKeyboardv:
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
	movl	$0, _ZL12keyBufferPos
	.loc 1 34 0
	subl	$8, %esp
	pushl	$_ZL16keyboardCallback11registers_t
	pushl	$33
	call	_Z24registerInterruptHandlerhPFv11registers_tE
	addl	$16, %esp
	.loc 1 35 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_Z12initKeyboardv, .-_Z12initKeyboardv
	.globl	_Z17getKeyboardBufferPct
	.type	_Z17getKeyboardBufferPct, @function
_Z17getKeyboardBufferPct:
.LFB2:
	.loc 1 38 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movw	%ax, -28(%ebp)
	.loc 1 39 0
	movl	_ZL12keyBufferPos, %eax
	movw	%ax, -10(%ebp)
	.loc 1 41 0
	movzwl	-28(%ebp), %eax
	cmpw	-10(%ebp), %ax
	jnb	.L7
	.loc 1 41 0 is_stmt 0 discriminator 1
	movzwl	-28(%ebp), %eax
	jmp	.L8
.L7:
	.loc 1 41 0 discriminator 2
	movzwl	-10(%ebp), %eax
.L8:
	.loc 1 41 0 discriminator 4
	movw	%ax, -12(%ebp)
	.loc 1 43 0 is_stmt 1 discriminator 4
	cmpl	$0, 8(%ebp)
	jne	.L9
	.loc 1 45 0
	movl	$0, %eax
	jmp	.L10
.L9:
	.loc 1 47 0
	movzwl	-12(%ebp), %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$_ZL9keyBuffer
	pushl	8(%ebp)
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 51 0
/APP
/  51 "drivers/keyboard.cpp" 1
	cli
/  0 "" 2
	.loc 1 52 0
/NO_APP
	movl	_ZL12keyBufferPos, %edx
	movzwl	-12(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movzwl	-10(%ebp), %eax
	addl	$_ZL9keyBuffer, %eax
	subl	$4, %esp
	pushl	%edx
	pushl	%eax
	pushl	$_ZL9keyBuffer
	call	_Z6memcpyPcS_j
	addl	$16, %esp
	.loc 1 53 0
	movl	_ZL12keyBufferPos, %edx
	movzwl	-12(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, _ZL12keyBufferPos
	.loc 1 54 0
/APP
/  54 "drivers/keyboard.cpp" 1
	sti
/  0 "" 2
	.loc 1 57 0
/NO_APP
	movzwl	-12(%ebp), %eax
.L10:
	.loc 1 58 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	_Z17getKeyboardBufferPct, .-_Z17getKeyboardBufferPct
.Letext0:
	.file 2 "includes/hw/types.h"
	.file 3 "includes/hw/isr.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x23e
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF24
	.byte	0x4
	.long	.LASF25
	.long	.LASF26
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
	.long	.LASF27
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
	.uleb128 0x8
	.long	0x16b
	.long	0x164
	.uleb128 0x9
	.long	0x164
	.value	0x3ff
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF15
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF16
	.uleb128 0xa
	.long	.LASF17
	.byte	0x1
	.byte	0x7
	.long	0x153
	.uleb128 0x5
	.byte	0x3
	.long	_ZL9keyBuffer
	.uleb128 0xa
	.long	.LASF18
	.byte	0x1
	.byte	0x8
	.long	0x45
	.uleb128 0x5
	.byte	0x3
	.long	_ZL12keyBufferPos
	.uleb128 0xb
	.long	.LASF28
	.byte	0x1
	.byte	0x25
	.long	.LASF29
	.long	0x4c
	.long	.LFB2
	.long	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ea
	.uleb128 0xc
	.long	.LASF19
	.byte	0x1
	.byte	0x25
	.long	0x1ea
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xc
	.long	.LASF20
	.byte	0x1
	.byte	0x25
	.long	0x4c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xd
	.string	"pos"
	.byte	0x1
	.byte	0x27
	.long	0x4c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -18
	.uleb128 0xd
	.string	"len"
	.byte	0x1
	.byte	0x29
	.long	0x4c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x16b
	.uleb128 0xf
	.long	.LASF30
	.byte	0x1
	.byte	0x1f
	.long	.LASF31
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x10
	.long	.LASF32
	.byte	0x1
	.byte	0xb
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xc
	.long	.LASF21
	.byte	0x1
	.byte	0xb
	.long	0x148
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xa
	.long	.LASF22
	.byte	0x1
	.byte	0xd
	.long	0x65
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
	.uleb128 0xa
	.long	.LASF23
	.byte	0x1
	.byte	0xe
	.long	0x65
	.uleb128 0x2
	.byte	0x91
	.sleb128 -18
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
	.uleb128 0x5
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
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
.LASF29:
	.string	"_Z17getKeyboardBufferPct"
.LASF16:
	.string	"char"
.LASF22:
	.string	"scancode"
.LASF30:
	.string	"initKeyboard"
.LASF11:
	.string	"err_code"
.LASF20:
	.string	"bufferLen"
.LASF13:
	.string	"useresp"
.LASF8:
	.string	"unsigned char"
.LASF15:
	.string	"long unsigned int"
.LASF5:
	.string	"short unsigned int"
.LASF17:
	.string	"keyBuffer"
.LASF18:
	.string	"keyBufferPos"
.LASF31:
	.string	"_Z12initKeyboardv"
.LASF23:
	.string	"scanmasked"
.LASF2:
	.string	"unsigned int"
.LASF0:
	.string	"long long unsigned int"
.LASF21:
	.string	"regs"
.LASF10:
	.string	"int_no"
.LASF4:
	.string	"UInt16"
.LASF3:
	.string	"UInt32"
.LASF14:
	.string	"registers_t"
.LASF12:
	.string	"eflags"
.LASF28:
	.string	"getKeyboardBuffer"
.LASF1:
	.string	"long long int"
.LASF24:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF6:
	.string	"short int"
.LASF19:
	.string	"buffer"
.LASF26:
	.string	"/home/alexis/src/hydrogen"
.LASF27:
	.string	"11registers_t"
.LASF7:
	.string	"UInt8"
.LASF25:
	.string	"drivers/keyboard.cpp"
.LASF9:
	.string	"signed char"
.LASF32:
	.string	"keyboardCallback"
	.ident	"GCC: (GNU) 7.2.0"
