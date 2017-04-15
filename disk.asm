; load 'dh' sectors from drive 'dl' into ES:BX, starting at sector 'cl'
disk_load:
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
  jc disk_error

  pop dx
  cmp al, dh
  jne sectors_error
disk_done:
  popa
  ret

disk_error:
  mov bx, DISK_ERROR
  call print
  call print_nl
  mov dh, ah ; ah = error code, dl = disk drive that errored
  call print_hex
  pop dx
  jmp disk_done
sectors_error:
  mov bx, SECTORS_ERROR
  call print
  call print_nl
  jmp disk_done

DISK_READ: db "Disk successfully read!", 0
DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
