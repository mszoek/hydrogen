; Kernel loader stub to get the right entry point from bootloader
; Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.

[bits 32]
global start
extern kernelMain


start:
; set up PAE paging with tables at 0x1000
	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 0x1000
	rep stosd ; clear the memory
	mov edi, cr3

; now we have
;  PML4T at 0x1000
;  PDPT at 0x2000
;  PDT at 0x3000
;  PT at 0x4000

	mov DWORD [edi], 0x2003 ; point PML4T to PDPT
	add edi, 0x1000
	mov DWORD [edi], 0x3003 ; point PDPT to PDT
	add edi, 0x1000
	mov DWORD [edi], 0x4003 ; point PDT to PT
	add edi, 0x1000

; identity map 2MB
	mov eax, ebx	; bootloader put stuff here
	mov ebx, 0x00000003
	mov ecx, 0x200 ; 512 entries
setEntry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop setEntry
	mov ebx, eax

; tell the CPU we're using PAE
	mov eax, cr4
	or eax, 1<<5
	mov cr4, eax

; set the LM bit to enable Long Mode
; we will be in 32-bit Compatibility Mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1<<8
	wrmsr
; enable paging
	mov eax, cr0
	or eax, 1<<31
	mov cr0, eax

; now we can enter true 64-bit mode!
; load the GDT and jump to the stub64
	lgdt [GDT64.Pointer]
	jmp GDT64.Code:stub64

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



[bits 64]
stub64:
	mov ax, GDT64.Data ; update the segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, GDT64.Null
	mov ss, ax
	mov rbp, _sys_stack
	mov rsp, rbp

	mov rsi, end
	sub rsi, 0x100000
	mov rdi, rbx
	push rdi
	push rsi
	jmp kernelMain		; nu kör vi!!
	cli
die: hlt
	jmp die

%include "kernel/gdt64.asm"

section .bss
	resb 256*1024

_sys_stack:

