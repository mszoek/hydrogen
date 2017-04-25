; This file contains the main bootloader for H2OS.
;
; Alexis Knox & Zoe Knox
; Created April 12, 2017

STG2_ADDR equ 0x7e00

[org 0x7c00] ; bootloader offset
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov ax,3  ; VGA text mode
    int 0x10

    mov bx, msg_startup
    call print
    call print_nl

; Load the stage2 from sector 2
    mov bx, STG2_ADDR
    mov dh, 1
    mov dl, 0x80
    mov cl, 2
    call disk_load

    call switch_to_pm
    jmp $ ; this will actually never be executed

%include "data/strings.asm"
%include "utilities/16bit/print.asm"
%include "utilities/16bit/disk.asm"
%include "utilities/32bit/32bit-gdt.asm"
%include "utilities/32bit/32bit-print.asm"
%include "utilities/32bit/32bit-switch.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
    mov ebx, MSG_PROT_MODE
    call print_string_pm ; Note that this will be written at the top left corner
    ;call STG2_ADDR
    jmp $

; bootsector
times 510-($-$$) db 0
dw 0xaa55
