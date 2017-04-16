[bits 16]
mov bx, MSG_STAGE2
call print
jmp $
[bits 32]
BEGIN_PM: ; after the switch, we get here
  mov ebx, MSG_PROT_MODE
  ;call print_string_pm
  jmp $

%include "utilities/32bit/32bit-gdt.asm"
%include "utilities/32bit/32bit-switch.asm"
%include "utilities/32bit/32bit-print.asm"
%include "utilities/16bit/print.asm"

MSG_STAGE2 db "Successfully entered stage 2 of loading.", 0
MSG_PROT_MODE db "Successfully entered 32bit Protected Mode!", 0
