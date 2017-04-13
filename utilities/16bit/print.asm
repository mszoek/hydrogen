; This file contains the main print function for
; 16-bit real mode.
;
; Alexis Knox
; Created April 12, 2017

print:
  pusha
do_print:
  mov al, [bx]
  cmp al, 0
  je done_print
  mov ah, 0x0e
  int 0x10
  add bx, 1
  jmp do_print
done_print:
  popa
  ret

; New line
print_nl:
  pusha
  mov ah, 0x0e
  mov al, 0x0a ; newline char
  int 0x10
  mov al, 0x0d ; carriage return
  int 0x10
  popa
  ret

; HEX PRINT BELOW

print_hex:
  pusha
  mov cx, 0 ; index variable

hex_loop:
  cmp cx, 4 ; loop 4 times
  je end

  ; 1. convert last char of dx to ascii
  mov ax, dx ; use ax as working register
  and ax, 0x000f
  add al, 0x30
  cmp al, 0x39
  jle step2
  add al, 7

step2:
  ; 2. get correct position of string to place ascii char
  ; bx <- base address + string length - index of char
  mov bx, HEX_OUT + 5 ; base + length
  sub bx, cx ; index variable
  mov [bx], al ;copy ascii char on 'al' to position pointed to by 'bx'
  ror dx, 4

  add cx, 1
  jmp hex_loop

end:
  ; prepare the parameter and call the function
  ; print receives parameters in 'bx'
  mov bx, HEX_OUT
  call print
  popa
  ret

HEX_OUT:
  db '0x0000', 0 ; reserve memory for new string
