; Kernel loader stub to get the right entry point from bootloader
; Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.

[bits 32]
global start
extern kernelMain
extern pml4t
extern pdpt
extern pdt
extern pt

start:
; set up PAE paging
	mov edi, pml4t
	mov cr3, edi
	xor eax, eax
	mov ecx, 0x1000
	rep stosd ; clear the memory
	mov edi, cr3

	mov eax, ebx	; save ebx. GRUB put stuff there

	mov ebx, pdpt
	or ebx, 3
	mov DWORD [edi], ebx ; point PML4T to PDPT

	mov edi, pdpt
	mov ebx, pdt
	or ebx, 3
	mov DWORD [edi], ebx ; point PDPT to PDT

	mov edi, pdt
	mov ebx, pt
	or ebx, 3
	mov DWORD [edi], ebx ; point PDT[0] to PT[0]
	add ebx, 0x1000
	add edi, 8
	mov DWORD [edi], ebx ; point PDT[1] to PT[1]
	
	mov edi, pt

; identity map first 4MB (pt[0-1023])
	mov ebx, 0x3
	mov ecx, 0x400 ; 1024 entries
setEntry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop setEntry

; ; we'll map the kernel at 3GB (0xC0000000)
; ; give it 8MB of space to start
; ; create PDT and page tables at 0x20000
; 	mov edi, 0x20000
; 	mov ebx, 0x21003
; 	mov ecx, 4
; setPDT:
; 	mov DWORD [edi], ebx
; 	add edi, 8
; 	add ebx, 0x1000
; 	loop setPDT

; 	mov edi, 0x21000
; 	mov ebx, 0x100003 ; phys address
; 	mov ecx, 0x1000
; setEntry2:
; 	mov DWORD [edi], ebx
; 	add edi, 8
; 	add ebx, 0x1000
; 	loop setEntry2

; ; hook up our new PDT in the PDPT
; 	mov edi, 0x2018
; 	mov ebx, 0x20003
; 	mov DWORD [edi], ebx

	mov ebx, eax ; restore bootloader info

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
	extern begin, code, bss, end

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
	; mov rax, 0xC0000000
	sub rsi, 0x100000
	mov rdi, rbx
	push rdi
	push rsi
	mov rax, qword kernelMain
	; mov rcx, qword 0xBFF00000
	; add rax, rcx
	jmp rax ; nu kör vi!!
	cli
die: hlt
	jmp die

%include "kernel/gdt64.asm"

section .bss
	resb 256*1024
_sys_stack:

