	.file	"kmem.cpp"
	.text
.Ltext0:
	.local	_ZL14physMemorySize
	.comm	_ZL14physMemorySize,4,4
	.local	_ZL14physUsedBlocks
	.comm	_ZL14physUsedBlocks,4,4
	.local	_ZL13physMaxBlocks
	.comm	_ZL13physMaxBlocks,4,4
	.local	_ZL13physMemoryMap
	.comm	_ZL13physMemoryMap,4,4
	.globl	regionType
	.section	.rodata
.LC0:
	.string	"Available"
.LC1:
	.string	"Reserved"
.LC2:
	.string	"ACPI Reclaim"
.LC3:
	.string	"ACPI NVS"
	.data
	.align 4
	.type	regionType, @object
	.size	regionType, 16
regionType:
	.long	.LC0
	.long	.LC1
	.long	.LC2
	.long	.LC3
	.text
	.type	_ZL12pmmBitmapSeti, @function
_ZL12pmmBitmapSeti:
.LFB0:
	.file 1 "kernel/kmem.cpp"
	.loc 1 20 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	.loc 1 21 0
	movl	_ZL13physMemoryMap, %edx
	movl	8(%ebp), %eax
	leal	31(%eax), %ecx
	testl	%eax, %eax
	cmovs	%ecx, %eax
	sarl	$5, %eax
	movl	%eax, %esi
	movl	%esi, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %ebx
	movl	8(%ebp), %eax
	cltd
	shrl	$27, %edx
	addl	%edx, %eax
	andl	$31, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, %ecx
	movl	_ZL13physMemoryMap, %eax
	movl	%esi, %edx
	sall	$2, %edx
	addl	%edx, %eax
	orl	%ecx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	.loc 1 22 0
	nop
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	_ZL12pmmBitmapSeti, .-_ZL12pmmBitmapSeti
	.type	_ZL14pmmBitmapUnseti, @function
_ZL14pmmBitmapUnseti:
.LFB1:
	.loc 1 25 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	.loc 1 26 0
	movl	_ZL13physMemoryMap, %edx
	movl	8(%ebp), %eax
	leal	31(%eax), %ecx
	testl	%eax, %eax
	cmovs	%ecx, %eax
	sarl	$5, %eax
	movl	%eax, %esi
	movl	%esi, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %ebx
	movl	8(%ebp), %eax
	cltd
	shrl	$27, %edx
	addl	%edx, %eax
	andl	$31, %eax
	subl	%edx, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	notl	%eax
	movl	%eax, %ecx
	movl	_ZL13physMemoryMap, %eax
	movl	%esi, %edx
	sall	$2, %edx
	addl	%edx, %eax
	andl	%ecx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	.loc 1 27 0
	nop
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	_ZL14pmmBitmapUnseti, .-_ZL14pmmBitmapUnseti
	.globl	_Z10pmmMemSizev
	.type	_Z10pmmMemSizev, @function
_Z10pmmMemSizev:
.LFB3:
	.loc 1 36 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 37 0
	movl	_ZL14physMemorySize, %eax
	.loc 1 38 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	_Z10pmmMemSizev, .-_Z10pmmMemSizev
	.globl	_Z16pmmMemSizeBlocksv
	.type	_Z16pmmMemSizeBlocksv, @function
_Z16pmmMemSizeBlocksv:
.LFB4:
	.loc 1 42 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 43 0
	movl	_ZL14physMemorySize, %eax
	shrl	$12, %eax
	.loc 1 44 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	_Z16pmmMemSizeBlocksv, .-_Z16pmmMemSizeBlocksv
	.globl	_Z10pmmMemFreev
	.type	_Z10pmmMemFreev, @function
_Z10pmmMemFreev:
.LFB5:
	.loc 1 48 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 49 0
	movl	_ZL14physMemorySize, %eax
	movl	_ZL14physUsedBlocks, %edx
	sall	$2, %edx
	subl	%edx, %eax
	andl	$4194303, %eax
	.loc 1 50 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	_Z10pmmMemFreev, .-_Z10pmmMemFreev
	.globl	_Z16pmmMemFreeBlocksv
	.type	_Z16pmmMemFreeBlocksv, @function
_Z16pmmMemFreeBlocksv:
.LFB6:
	.loc 1 54 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 55 0
	movl	_ZL13physMaxBlocks, %edx
	movl	_ZL14physUsedBlocks, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	.loc 1 56 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_Z16pmmMemFreeBlocksv, .-_Z16pmmMemFreeBlocksv
	.globl	_Z16pmmFindFirstFreev
	.type	_Z16pmmFindFirstFreev, @function
_Z16pmmFindFirstFreev:
.LFB7:
	.loc 1 59 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
.LBB2:
	.loc 1 62 0
	movl	$0, -4(%ebp)
.L18:
	.loc 1 62 0 is_stmt 0 discriminator 1
	call	_Z16pmmMemSizeBlocksv
	shrl	$5, %eax
	cmpl	%eax, -4(%ebp)
	setb	%al
	testb	%al, %al
	je	.L12
.LBB3:
.LBB4:
	.loc 1 64 0 is_stmt 1
	movl	_ZL13physMemoryMap, %eax
	movl	-4(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	$-1, %eax
	je	.L13
.LBB5:
.LBB6:
	.loc 1 67 0
	movl	$0, -8(%ebp)
.L17:
	.loc 1 67 0 is_stmt 0 discriminator 1
	cmpl	$31, -8(%ebp)
	jg	.L13
.LBB7:
	.loc 1 69 0 is_stmt 1
	movl	-8(%ebp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -12(%ebp)
	.loc 1 70 0
	movl	_ZL13physMemoryMap, %eax
	movl	-4(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	andl	%edx, %eax
	testl	%eax, %eax
	jne	.L15
	.loc 1 71 0
	movl	-4(%ebp), %eax
	sall	$5, %eax
	movl	%eax, %edx
	movl	-8(%ebp), %eax
	addl	%edx, %eax
	jmp	.L16
.L15:
.LBE7:
	.loc 1 67 0 discriminator 2
	addl	$1, -8(%ebp)
	jmp	.L17
.L13:
.LBE6:
.LBE5:
.LBE4:
.LBE3:
	.loc 1 62 0 discriminator 2
	addl	$1, -4(%ebp)
	jmp	.L18
.L12:
.LBE2:
	.loc 1 75 0
	movl	$-1, %eax
.L16:
	.loc 1 76 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	_Z16pmmFindFirstFreev, .-_Z16pmmFindFirstFreev
	.section	.rodata
.LC4:
	.string	"Region "
.LC5:
	.string	": start "
.LC6:
	.string	", len "
.LC7:
	.string	" "
.LC8:
	.string	"\n"
.LC9:
	.string	"PMM initialized: "
.LC10:
	.string	" blocks. Used/reserved: "
.LC11:
	.string	" blocks, Free: "
.LC12:
	.string	" blocks\n\n"
	.text
	.globl	_Z7pmmInitjjjP10regionInfoj
	.type	_Z7pmmInitjjjP10regionInfoj, @function
_Z7pmmInitjjjP10regionInfoj:
.LFB8:
	.loc 1 79 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$88, %esp
	.loc 1 83 0
	movl	8(%ebp), %eax
	movl	%eax, _ZL14physMemorySize
	.loc 1 84 0
	movl	12(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZL13physMemoryMap
	.loc 1 85 0
	call	_Z10pmmMemSizev
	sall	$10, %eax
	shrl	$12, %eax
	movl	%eax, _ZL13physMaxBlocks
	.loc 1 86 0
	call	_Z16pmmMemSizeBlocksv
	movl	%eax, _ZL14physUsedBlocks
	.loc 1 89 0
	call	_Z16pmmMemSizeBlocksv
	shrl	$3, %eax
	movl	%eax, %edx
	movl	_ZL13physMemoryMap, %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$15
	pushl	%eax
	call	_Z6memsetPcci
	addl	$16, %esp
	.loc 1 91 0
	cmpl	$0, 20(%ebp)
	je	.L27
	.loc 1 93 0
	movl	$0, -12(%ebp)
.L26:
	.loc 1 93 0 is_stmt 0 discriminator 1
	movl	24(%ebp), %eax
	movl	$-1431655765, %edx
	mull	%edx
	shrl	$4, %edx
	movl	-12(%ebp), %eax
	cmpl	%eax, %edx
	jbe	.L22
	.loc 1 95 0 is_stmt 1
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	16(%eax), %eax
	cmpl	$3, %eax
	jbe	.L23
	.loc 1 97 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	$1, 16(%eax)
.L23:
	.loc 1 100 0
	cmpl	$0, -12(%ebp)
	jle	.L24
	.loc 1 100 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L28
.L24:
	.loc 1 104 0 is_stmt 1
	subl	$12, %esp
	pushl	$.LC4
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 105 0
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	-12(%ebp)
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 106 0
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 107 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%ecx, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 108 0
	subl	$12, %esp
	pushl	$.LC5
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 109 0
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 110 0
	subl	$12, %esp
	pushl	$.LC6
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 111 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	addl	%ecx, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 112 0
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 113 0
	subl	$12, %esp
	pushl	$.LC7
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 114 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	16(%eax), %eax
	movl	regionType(,%eax,4), %eax
	subl	$12, %esp
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 115 0
	subl	$12, %esp
	pushl	$.LC8
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 118 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	16(%eax), %eax
	cmpl	$1, %eax
	jne	.L25
	.loc 1 120 0
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	%ecx
	pushl	%eax
	call	_Z13pmmInitRegionjj
	addl	$16, %esp
.L25:
	.loc 1 93 0 discriminator 2
	addl	$1, -12(%ebp)
	jmp	.L26
.L28:
	.loc 1 101 0
	nop
.L22:
	.loc 1 125 0 discriminator 1
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	12(%ebp)
	call	_Z13pmmDropRegionjj
	addl	$16, %esp
	.loc 1 127 0 discriminator 1
	subl	$12, %esp
	pushl	$.LC9
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 128 0 discriminator 1
	movl	_ZL13physMaxBlocks, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 129 0 discriminator 1
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 130 0 discriminator 1
	subl	$12, %esp
	pushl	$.LC10
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 131 0 discriminator 1
	movl	_ZL14physUsedBlocks, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 132 0 discriminator 1
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 133 0 discriminator 1
	subl	$12, %esp
	pushl	$.LC11
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 134 0 discriminator 1
	movl	_ZL13physMaxBlocks, %edx
	movl	_ZL14physUsedBlocks, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	subl	$8, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	pushl	%edx
	call	_Z4itoaiPc
	addl	$16, %esp
	.loc 1 135 0 discriminator 1
	subl	$12, %esp
	leal	-76(%ebp), %eax
	pushl	%eax
	call	_Z6kprintPc
	addl	$16, %esp
	.loc 1 136 0 discriminator 1
	subl	$12, %esp
	pushl	$.LC12
	call	_Z6kprintPc
	addl	$16, %esp
	jmp	.L19
.L27:
	.loc 1 91 0
	nop
.L19:
	.loc 1 137 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	_Z7pmmInitjjjP10regionInfoj, .-_Z7pmmInitjjjP10regionInfoj
	.globl	_Z13pmmInitRegionjj
	.type	_Z13pmmInitRegionjj, @function
_Z13pmmInitRegionjj:
.LFB9:
	.loc 1 140 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 141 0
	movl	8(%ebp), %eax
	shrl	$12, %eax
	movl	%eax, -4(%ebp)
	.loc 1 142 0
	movl	12(%ebp), %eax
	shrl	$12, %eax
	movl	%eax, -8(%ebp)
.L31:
	.loc 1 144 0 discriminator 2
	cmpl	$0, -8(%ebp)
	jle	.L30
	.loc 1 146 0 discriminator 1
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	pushl	%eax
	call	_ZL14pmmBitmapUnseti
	addl	$4, %esp
	.loc 1 147 0 discriminator 1
	movl	_ZL14physUsedBlocks, %eax
	subl	$1, %eax
	movl	%eax, _ZL14physUsedBlocks
	.loc 1 144 0 discriminator 1
	subl	$1, -8(%ebp)
	jmp	.L31
.L30:
	.loc 1 149 0
	pushl	$0
	call	_ZL12pmmBitmapSeti
	addl	$4, %esp
	.loc 1 150 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	_Z13pmmInitRegionjj, .-_Z13pmmInitRegionjj
	.globl	_Z13pmmDropRegionjj
	.type	_Z13pmmDropRegionjj, @function
_Z13pmmDropRegionjj:
.LFB10:
	.loc 1 153 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 154 0
	movl	8(%ebp), %eax
	shrl	$12, %eax
	movl	%eax, -4(%ebp)
	.loc 1 155 0
	movl	12(%ebp), %eax
	shrl	$12, %eax
	movl	%eax, -8(%ebp)
.L34:
	.loc 1 157 0 discriminator 2
	cmpl	$0, -8(%ebp)
	jle	.L35
	.loc 1 159 0 discriminator 1
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	pushl	%eax
	call	_ZL12pmmBitmapSeti
	addl	$4, %esp
	.loc 1 160 0 discriminator 1
	movl	_ZL14physUsedBlocks, %eax
	addl	$1, %eax
	movl	%eax, _ZL14physUsedBlocks
	.loc 1 157 0 discriminator 1
	subl	$1, -8(%ebp)
	jmp	.L34
.L35:
	.loc 1 162 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	_Z13pmmDropRegionjj, .-_Z13pmmDropRegionjj
	.globl	_Z8pmmAllocv
	.type	_Z8pmmAllocv, @function
_Z8pmmAllocv:
.LFB11:
	.loc 1 165 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 169 0
	call	_Z16pmmMemFreeBlocksv
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	.L37
	.loc 1 170 0
	movl	$0, %eax
	jmp	.L38
.L37:
	.loc 1 172 0
	call	_Z16pmmFindFirstFreev
	movl	%eax, -4(%ebp)
	.loc 1 173 0
	cmpl	$-1, -4(%ebp)
	jne	.L39
	.loc 1 174 0
	movl	$0, %eax
	jmp	.L38
.L39:
	.loc 1 176 0
	pushl	-4(%ebp)
	call	_ZL12pmmBitmapSeti
	addl	$4, %esp
	.loc 1 177 0
	movl	-4(%ebp), %eax
	sall	$12, %eax
	movl	%eax, -8(%ebp)
	.loc 1 178 0
	movl	_ZL14physUsedBlocks, %eax
	addl	$1, %eax
	movl	%eax, _ZL14physUsedBlocks
	.loc 1 180 0
	movl	-8(%ebp), %eax
.L38:
	.loc 1 181 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	_Z8pmmAllocv, .-_Z8pmmAllocv
	.globl	_Z7pmmFreePv
	.type	_Z7pmmFreePv, @function
_Z7pmmFreePv:
.LFB12:
	.loc 1 184 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 185 0
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	.loc 1 186 0
	movl	-4(%ebp), %eax
	shrl	$12, %eax
	movl	%eax, -8(%ebp)
	.loc 1 188 0
	pushl	-8(%ebp)
	call	_ZL14pmmBitmapUnseti
	addl	$4, %esp
	.loc 1 189 0
	movl	_ZL14physUsedBlocks, %eax
	subl	$1, %eax
	movl	%eax, _ZL14physUsedBlocks
	.loc 1 190 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	_Z7pmmFreePv, .-_Z7pmmFreePv
	.globl	_Z6memcpyPcS_j
	.type	_Z6memcpyPcS_j, @function
_Z6memcpyPcS_j:
.LFB13:
	.loc 1 194 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 196 0
	movl	$0, -4(%ebp)
.L43:
	.loc 1 196 0 is_stmt 0 discriminator 3
	movl	-4(%ebp), %eax
	cmpl	%eax, 16(%ebp)
	jbe	.L44
	.loc 1 198 0 is_stmt 1 discriminator 2
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	-4(%ebp), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movzbl	(%eax), %eax
	movb	%al, (%edx)
	.loc 1 196 0 discriminator 2
	addl	$1, -4(%ebp)
	jmp	.L43
.L44:
	.loc 1 200 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	_Z6memcpyPcS_j, .-_Z6memcpyPcS_j
	.globl	_Z6memsetPcci
	.type	_Z6memsetPcci, @function
_Z6memsetPcci:
.LFB14:
	.loc 1 203 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	12(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 204 0
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
.L47:
	.loc 1 205 0 discriminator 2
	cmpl	$0, 16(%ebp)
	jle	.L48
	.loc 1 207 0 discriminator 1
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movzbl	-20(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 205 0 discriminator 1
	subl	$1, 16(%ebp)
	jmp	.L47
.L48:
	.loc 1 209 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE14:
	.size	_Z6memsetPcci, .-_Z6memsetPcci
.Letext0:
	.file 2 "includes/kmem.h"
	.file 3 "includes/hw/types.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x499
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF54
	.byte	0x4
	.long	.LASF55
	.long	.LASF56
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
	.long	.LASF57
	.byte	0x3
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
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x5
	.long	.LASF58
	.byte	0x18
	.byte	0x2
	.byte	0xb
	.long	0xbd
	.uleb128 0x6
	.long	.LASF7
	.byte	0x2
	.byte	0xd
	.long	0x33
	.byte	0
	.uleb128 0x6
	.long	.LASF8
	.byte	0x2
	.byte	0xe
	.long	0x33
	.byte	0x4
	.uleb128 0x6
	.long	.LASF9
	.byte	0x2
	.byte	0xf
	.long	0x33
	.byte	0x8
	.uleb128 0x6
	.long	.LASF10
	.byte	0x2
	.byte	0x10
	.long	0x33
	.byte	0xc
	.uleb128 0x6
	.long	.LASF11
	.byte	0x2
	.byte	0x11
	.long	0x33
	.byte	0x10
	.uleb128 0x6
	.long	.LASF12
	.byte	0x2
	.byte	0x12
	.long	0x33
	.byte	0x14
	.byte	0
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x8
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	_ZL14physMemorySize
	.uleb128 0x7
	.long	.LASF14
	.byte	0x1
	.byte	0x9
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	_ZL14physUsedBlocks
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0xa
	.long	0x33
	.uleb128 0x5
	.byte	0x3
	.long	_ZL13physMaxBlocks
	.uleb128 0x7
	.long	.LASF16
	.byte	0x1
	.byte	0xb
	.long	0x101
	.uleb128 0x5
	.byte	0x3
	.long	_ZL13physMemoryMap
	.uleb128 0x8
	.byte	0x4
	.long	0x33
	.uleb128 0x9
	.long	0x11e
	.long	0x117
	.uleb128 0xa
	.long	0x117
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF17
	.uleb128 0x8
	.byte	0x4
	.long	0x12b
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF18
	.uleb128 0xb
	.long	0x124
	.uleb128 0xc
	.long	.LASF59
	.byte	0x1
	.byte	0xd
	.long	0x107
	.uleb128 0x5
	.byte	0x3
	.long	regionType
	.uleb128 0xd
	.long	.LASF19
	.byte	0x1
	.byte	0xca
	.long	.LASF21
	.long	.LFB14
	.long	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x193
	.uleb128 0xe
	.string	"dst"
	.byte	0x1
	.byte	0xca
	.long	0x193
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xe
	.string	"val"
	.byte	0x1
	.byte	0xca
	.long	0x124
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xe
	.string	"len"
	.byte	0x1
	.byte	0xca
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0xf
	.string	"tmp"
	.byte	0x1
	.byte	0xcc
	.long	0x193
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0x124
	.uleb128 0xd
	.long	.LASF20
	.byte	0x1
	.byte	0xc1
	.long	.LASF22
	.long	.LFB13
	.long	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x1e9
	.uleb128 0xe
	.string	"dst"
	.byte	0x1
	.byte	0xc1
	.long	0x193
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xe
	.string	"src"
	.byte	0x1
	.byte	0xc1
	.long	0x193
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xe
	.string	"len"
	.byte	0x1
	.byte	0xc1
	.long	0x3e
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0xf
	.string	"i"
	.byte	0x1
	.byte	0xc3
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x10
	.long	.LASF23
	.byte	0x1
	.byte	0xb7
	.long	.LASF24
	.long	.LFB12
	.long	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x22b
	.uleb128 0xe
	.string	"p"
	.byte	0x1
	.byte	0xb7
	.long	0x22b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x7
	.long	.LASF25
	.byte	0x1
	.byte	0xb9
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x7
	.long	.LASF26
	.byte	0x1
	.byte	0xba
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x11
	.byte	0x4
	.uleb128 0x12
	.long	.LASF42
	.byte	0x1
	.byte	0xa4
	.long	.LASF44
	.long	0x22b
	.long	.LFB11
	.long	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x267
	.uleb128 0x7
	.long	.LASF26
	.byte	0x1
	.byte	0xa6
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x7
	.long	.LASF25
	.byte	0x1
	.byte	0xa7
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x10
	.long	.LASF27
	.byte	0x1
	.byte	0x98
	.long	.LASF28
	.long	.LFB10
	.long	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x2b9
	.uleb128 0x13
	.long	.LASF29
	.byte	0x1
	.byte	0x98
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF30
	.byte	0x1
	.byte	0x98
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x7
	.long	.LASF31
	.byte	0x1
	.byte	0x9a
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x7
	.long	.LASF32
	.byte	0x1
	.byte	0x9b
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x10
	.long	.LASF33
	.byte	0x1
	.byte	0x8b
	.long	.LASF34
	.long	.LFB9
	.long	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x30b
	.uleb128 0x13
	.long	.LASF29
	.byte	0x1
	.byte	0x8b
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF30
	.byte	0x1
	.byte	0x8b
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x7
	.long	.LASF31
	.byte	0x1
	.byte	0x8d
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x7
	.long	.LASF32
	.byte	0x1
	.byte	0x8e
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x10
	.long	.LASF35
	.byte	0x1
	.byte	0x4e
	.long	.LASF36
	.long	.LFB8
	.long	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x386
	.uleb128 0x13
	.long	.LASF37
	.byte	0x1
	.byte	0x4e
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF38
	.byte	0x1
	.byte	0x4e
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x13
	.long	.LASF39
	.byte	0x1
	.byte	0x4e
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x13
	.long	.LASF40
	.byte	0x1
	.byte	0x4e
	.long	0x386
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x13
	.long	.LASF41
	.byte	0x1
	.byte	0x4e
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0xf
	.string	"i"
	.byte	0x1
	.byte	0x50
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xf
	.string	"buf"
	.byte	0x1
	.byte	0x51
	.long	0x38c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.long	0x68
	.uleb128 0x9
	.long	0x124
	.long	0x39c
	.uleb128 0xa
	.long	0x117
	.byte	0x3f
	.byte	0
	.uleb128 0x12
	.long	.LASF43
	.byte	0x1
	.byte	0x3a
	.long	.LASF45
	.long	0x45
	.long	.LFB7
	.long	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x3f4
	.uleb128 0xf
	.string	"i"
	.byte	0x1
	.byte	0x3c
	.long	0x33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x14
	.long	.LBB5
	.long	.LBE5-.LBB5
	.uleb128 0xf
	.string	"j"
	.byte	0x1
	.byte	0x42
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x14
	.long	.LBB7
	.long	.LBE7-.LBB7
	.uleb128 0xf
	.string	"bit"
	.byte	0x1
	.byte	0x45
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x15
	.long	.LASF46
	.byte	0x1
	.byte	0x35
	.long	.LASF48
	.long	0x33
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.long	.LASF47
	.byte	0x1
	.byte	0x2f
	.long	.LASF49
	.long	0x33
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.long	.LASF50
	.byte	0x1
	.byte	0x29
	.long	.LASF51
	.long	0x33
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.long	.LASF52
	.byte	0x1
	.byte	0x23
	.long	.LASF53
	.long	0x33
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x16
	.long	.LASF60
	.byte	0x1
	.byte	0x18
	.long	.LFB1
	.long	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x47c
	.uleb128 0xe
	.string	"bit"
	.byte	0x1
	.byte	0x18
	.long	0x45
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.long	.LASF61
	.byte	0x1
	.byte	0x13
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.string	"bit"
	.byte	0x1
	.byte	0x13
	.long	0x45
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x11
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
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
.LASF45:
	.string	"_Z16pmmFindFirstFreev"
.LASF25:
	.string	"addr"
.LASF35:
	.string	"pmmInit"
.LASF51:
	.string	"_Z16pmmMemSizeBlocksv"
.LASF52:
	.string	"pmmMemSize"
.LASF7:
	.string	"startLo"
.LASF16:
	.string	"physMemoryMap"
.LASF31:
	.string	"align"
.LASF13:
	.string	"physMemorySize"
.LASF46:
	.string	"pmmMemFreeBlocks"
.LASF59:
	.string	"regionType"
.LASF22:
	.string	"_Z6memcpyPcS_j"
.LASF27:
	.string	"pmmDropRegion"
.LASF34:
	.string	"_Z13pmmInitRegionjj"
.LASF21:
	.string	"_Z6memsetPcci"
.LASF38:
	.string	"kernAddr"
.LASF39:
	.string	"kernSize"
.LASF33:
	.string	"pmmInitRegion"
.LASF55:
	.string	"kernel/kmem.cpp"
.LASF47:
	.string	"pmmMemFree"
.LASF17:
	.string	"long unsigned int"
.LASF3:
	.string	"short unsigned int"
.LASF41:
	.string	"regionsLen"
.LASF49:
	.string	"_Z10pmmMemFreev"
.LASF36:
	.string	"_Z7pmmInitjjjP10regionInfoj"
.LASF5:
	.string	"unsigned char"
.LASF19:
	.string	"memset"
.LASF12:
	.string	"acpi30"
.LASF60:
	.string	"pmmBitmapUnset"
.LASF24:
	.string	"_Z7pmmFreePv"
.LASF23:
	.string	"pmmFree"
.LASF29:
	.string	"base"
.LASF2:
	.string	"unsigned int"
.LASF37:
	.string	"memSize"
.LASF28:
	.string	"_Z13pmmDropRegionjj"
.LASF0:
	.string	"long long unsigned int"
.LASF53:
	.string	"_Z10pmmMemSizev"
.LASF57:
	.string	"UInt32"
.LASF44:
	.string	"_Z8pmmAllocv"
.LASF32:
	.string	"blocks"
.LASF14:
	.string	"physUsedBlocks"
.LASF48:
	.string	"_Z16pmmMemFreeBlocksv"
.LASF1:
	.string	"long long int"
.LASF40:
	.string	"regions"
.LASF18:
	.string	"char"
.LASF54:
	.string	"GNU C++14 7.2.0 -m32 -mno-red-zone -mtune=generic -march=pentiumpro -g -ffreestanding -fno-exceptions -fno-rtti -fpermissive"
.LASF58:
	.string	"regionInfo"
.LASF43:
	.string	"pmmFindFirstFree"
.LASF11:
	.string	"type"
.LASF4:
	.string	"short int"
.LASF10:
	.string	"sizeHi"
.LASF50:
	.string	"pmmMemSizeBlocks"
.LASF20:
	.string	"memcpy"
.LASF56:
	.string	"/home/alexis/src/hydrogen"
.LASF26:
	.string	"frame"
.LASF8:
	.string	"startHi"
.LASF6:
	.string	"signed char"
.LASF61:
	.string	"pmmBitmapSet"
.LASF30:
	.string	"size"
.LASF42:
	.string	"pmmAlloc"
.LASF15:
	.string	"physMaxBlocks"
.LASF9:
	.string	"sizeLo"
	.ident	"GCC: (GNU) 7.2.0"
