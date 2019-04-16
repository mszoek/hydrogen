; Kernel loader stub to get the right entry point from bootloader
; Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.

global start
global pml4t
global pdpt
global pdt
global pt
extern kernelMain
extern code, dataend, end

base    equ 0x7C00000000

section .multiboot
align 4
mboot:
	multiboot_page_align 	equ 1<<0
	multiboot_memory_info	equ 1<<1
	multiboot_gfx_info		equ 1<<2
	multiboot_header_magic	equ 0x1badb002
	multiboot_header_flags	equ multiboot_page_align | multiboot_memory_info | multiboot_gfx_info 
	multiboot_checksum		equ -(multiboot_header_magic + multiboot_header_flags)

	dd multiboot_header_magic
	dd multiboot_header_flags
	dd multiboot_checksum

	dd mboot
	dd code - base
	dd dataend - base
	dd end - base
	dd start
	dd 0	; mode = graphical
	dd 1920	; auto width (no preference)
	dd 1080	; auto height (no preference)
	dd 32	; prefer 32bpp

section .inittext
bits 32

binfaddr:
	dd 0
	dd 0

start:
	; save ebx. GRUB put stuff there
	mov edi, binfaddr
	mov [edi], ebx

	; set up PAE paging. we need to identity map the first few MB
	; so the loader can get to stub64. then we remove it.
	mov edi, pml4t - base
	mov cr3, edi
	xor eax, eax
	mov ecx, 0x1000
	rep stosd ; clear the memory

	mov edi, cr3
	mov ebx, pdpt - base
	or ebx, 3
	mov DWORD [edi], ebx ; point PML4T to PDPT

	mov edi, pdpt - base
	xor eax, eax
	mov ecx, 0x2000
	rep stosd ; clear memory

	mov edi, pdpt - base
	mov ebx, pdt - base
	or ebx, 3
	mov DWORD [edi], ebx ; point PDPT to PDT
	add edi, 0xf80
	add ebx, 0x1000
	mov DWORD [edi], ebx ; point PDPT[496] to PDT[512];

	mov edi, pdt - base
	xor eax, eax
	mov ecx, 0x3000
	rep stosd ; clear memory

	mov edi, pdt - base
	mov ebx, pt - base
	or ebx, 3
	mov DWORD [edi], ebx ; point PDT[0] to PT[0]
	add ebx, 0x1000
	add edi, 8
	mov DWORD [edi], ebx ; point PDT[1] to PT[512]

	mov edi, pdt - base
	add edi, 0x1000 ; base of our PDT for this 1GB
	mov ebx, pt - base
	add ebx, 0x2000
	or ebx, 3
	mov DWORD [edi], ebx
	add edi, 8
	add ebx, 0x1000
	mov DWORD [edi], ebx

	; identity map first 4MB (pt[0-1023])
	mov edi, pt - base
	mov ebx, 0x3
	mov ecx, 0x400 ; 1024 entries = 8KB
setEntry:
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop setEntry

	; map the same 4MB into 0x7C00000000
	mov edi, pt - base
	add edi, 0x2000
	mov ebx, 0x3
	mov ecx, 0x400
setEntry4:
	mov DWORD [edi], ebx
	add edi, 8
	add ebx, 0x1000
	loop setEntry4

	mov ebx, edx ; restore bootloader info

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
	; load the GDT and jump to stub64
	lgdt [GDT64.PointerLow - base]
	mov ax, GDT64.Data
	mov ds, ax
	mov es, ax
	mov ss, ax
	jmp GDT64.Code:stub64

bits 64
stub64:
	mov rax, start64
	jmp rax

section .text
start64:
	; now we're in the virtual address space!
	; reload the GDT and update selectors again
	mov rax, GDT64.Pointer
	lgdt [rax]

	mov ax, GDT64.Data
	mov ds, ax
	mov es, ax
	mov ss, ax
	jmp okgo

okgo:
	mov rsp, _sys_stack
	mov rbp, rsp
	mov rsi, end
	mov rdi, base
	sub rsi, rdi
	mov rdi, [binfaddr]

	push rdi ; what we saved from GRUB
	push rsi ; kernel size
	mov rax, QWORD kernelMain
	jmp rax ; nu kör vi!!
	cli
die: hlt
	jmp die

section .bss
align 4096
pml4t:	resb 8*512
pdpt:	resb 8*1024
pdt:	resb 8*1536
pt:		resb 8*32768

align 8
	resb 256*1024
_sys_stack:

section .rodata
align 8
%include "kernel/gdt64.asm"
