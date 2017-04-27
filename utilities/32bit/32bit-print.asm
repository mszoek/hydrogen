[bits 32] ; enable 32-bit protected mode

; define constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

printStringPM:
  pusha
  mov edx, VIDEO_MEMORY

printStringPM_loop:
  mov al, [ebx] ; ebx is the address of our char
  mov ah, WHITE_ON_BLACK

  cmp al, 0 ; check if it's the end of the string
  je printStringPM_done

  mov [edx], ax ; store char + attribute in video memory
  add ebx, 1 ; next char
  add edx, 2 ; next video memory position

  jmp printStringPM_loop

printStringPM_done:
  popa
  ret
