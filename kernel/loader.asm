; Kernel loader stub to get the right entry point from bootloader
; Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.

[bits 32]
global start
extern kernelMain


start:
	lgdt [gdt_descriptor] ; Load the GDT descriptor
	mov ax, 0x10 ; update the segment registers
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov esp, _sys_stack
	jmp 0x08:stublet

align 4
mboot:
	multiboot_page_align 	equ 1<<0
	multiboot_memory_info	equ 1<<1
	multiboot_gfx_info		equ 1<<2
	multiboot_aout_kludge	equ 1<<16
	multiboot_header_magic	equ 0x1badb002
	multiboot_header_flags	equ multiboot_page_align | multiboot_memory_info | multiboot_gfx_info | multiboot_aout_kludge
	multiboot_checksum		equ -(multiboot_header_magic + multiboot_header_flags)
	extern code, bss, end

	dd multiboot_header_magic
	dd multiboot_header_flags
	dd multiboot_checksum

	dd mboot
	dd code
	dd bss
	dd end
	dd start
	dd 0	; mode = graphical
	dd 1920	; auto width (no preference)
	dd 1080	; auto height (no preference)
	dd 32	; prefer 32bpp

stublet:
	mov eax, end
	sub eax, 0x100000
	push eax
	push ebx				; Pass multiboot info block to kernel
	call kernelMain			; nu kör vi!!
	cli
die: hlt
	jmp die

%include "utilities/32bit/32bit-gdt.asm"

section .bss
	resb 32768

_sys_stack:

