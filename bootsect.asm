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

  ; Read the info sector to get our stage2 location
  mov bx, INFOSECTOR
  mov dh, 1
  mov dl, 0x80
  mov cl, 2
  call disk_load

  mov dx, [ISMarker]
  mov ax, [ISMagic]
  cmp dx, ax
  jne ISLoadError
  mov dx, [ISMarker+2]
  mov ax, [ISMagic+2]
  cmp dx, ax
  jne ISLoadError

; Info Sector has been loaded!
  mov bx, MSG_LOAD_STG2
  call print
  mov dx, [ISStage2Start]
  call print_hex
  mov bx, MSG_SLASH
  call print
  mov dx, [ISStage2Len]
  call print_hex
  call print_nl

  mov bx, KERNEL_ADDR
  mov dh, [ISStage2Len]
  mov dl, 0x80
  mov cl, [ISStage2Start]
  call disk_load

  mov cx, 20
  mov si, KERNEL_ADDR
loop0:
  mov dx, [si]
  call print_hex
  mov bx, MSG_SPACE
  call print
  inc si
  inc si
  loop loop0

  jmp $ ; KERNEL_ADDR

ISLoadError:
  mov bx, MSG_INFOSECT_BAD_MAGIC
  call print
  jmp $   ; halt and catch fire


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
%include "data/infosect.asm"

KERNEL_ADDR equ 0x1000

times 510 - ($-$$) db 0
dw 0xaa55
