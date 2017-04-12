; This file contains the main print function for
; 16-bit real mode.
;
; Alexis Knox
; Created April 12, 2017

print:
  pusha
  call do_print
do_print:
  mov al, [bx]
  cmp al, 0
  je done_print
  mov ah, 0x0e
  int 0x10
  add bx, 1
  call do_print
done_print:
  popa
  ret
