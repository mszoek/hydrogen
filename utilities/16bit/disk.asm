; load 'dh' sectors from drive 'dl' into ES:BX, starting at sector 'cl'
diskLoad:
  pusha
  push dx

  ; first, reset the drive
resetdrive:
  mov ah, 0 ; reset command
  int 0x13
  jc resetdrive

  mov ah, 0x02
  mov al, dh
  mov ch, 0x00
  mov dh, 0x00
  int 0x13
  jc diskError

  pop dx
  cmp al, dh
  jne sectorsError
diskDone:
  popa
  ret

diskError:
  mov bx, msgDiskError
  call print
  call printNL
  mov dh, ah ; ah = error code, dl = disk drive that errored
  call printHex
  pop dx
  jmp diskDone
sectorsError:
  mov bx, msgSectorsError
  call print
  call printNL
  jmp diskDone

msgDiskError: db "Disk read error", 0
msgSectorsError: db "Disk: short read", 0
