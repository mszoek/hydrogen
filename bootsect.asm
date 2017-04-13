; This file contains the main bootloader for
; H2OS. It is minimal and still needs lots of work.
;
; Alexis Knox
; Created April 12, 2017

[bits 16]
[org 0x7c00]

begin:
  mov bx, msg_startup
  call print
  call print_nl

  ; Load 20 sectors from disk
  mov dh, 20
  mov dl, 0x80
  call disk_load

  jmp KERNEL_ADDR

;[bits 32]
;BEGIN_PM: ; after the switch, we get here
;  mov ebx, MSG_PROT_MODE
;  call print_string_pm
;  jmp $


%include "utilities/16bit/print.asm"
%include "disk.asm"
;%include "utilities/32bit/32bit-gdt.asm"
;%include "utilities/32bit/32bit-switch.asm"
%include "data/strings.asm"

KERNEL_ADDR equ 0x1000

times 510 - ($-$$) db 0
dw 0xaa55
