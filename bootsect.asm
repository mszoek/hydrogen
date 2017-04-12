; This file contains the main bootloader for
; H2OS. It is minimal and still needs lots of work.
;
; Alexis Knox
; Created April 12, 2017

[bits 16]
[org 0x7c00]

call begin
begin:
  mov bx, msg_startup
  call print

%include "utilities/16bit/print.asm"
%include "data/strings.asm"

times 510 - ($-$$) db 0
dw 0xaa55
