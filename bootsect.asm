; This file contains the main bootloader for H2OS.
;
; Alexis Knox & Zoe Knox
; Created April 12, 2017

stage2Addr equ 0x7e00
kernAddr equ 0x1000

[org 0x7c00] ; bootloader offset
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, msgStartup
    call print
    call printNL

; Load the stage2 from sector 2
    mov bx, stage2Addr
    mov dh, 1
    mov dl, 0x80
    mov cl, 2
    call diskLoad

; Read the volume header
    mov bx, HFSPSignature
    mov dh, 2
    mov dl, 0x80
    mov cl, 3
    call diskLoad

    mov dx, HFSPMagic
    cmp dx, [HFSPSignature]
    jne BadHFSSignature

    mov byte [DAPlen], 0x10
    mov byte [DAPreserved], 0
    mov cx, [HFSPStartupFile+22]  ; only the low 16 bits
    mov dh, ch  ; ntohs
    mov ch, cl
    mov cl, dh
    shl cx, 3   ; convert to 512 byte sectors
    mov word [DAPblocks], cx
    mov dword [DAPbuffer], kernAddr

    mov dx, [HFSPStartupFile+16]
    mov ch, dh  ; ntohs
    mov dh, dl
    mov dl, ch
    mov [HFSPStartupFile+16], dx
    mov dx, [HFSPStartupFile+18]
    mov ch, dh  ; ntohs
    mov dh, dl
    mov dl, ch
    mov [HFSPStartupFile+18], dx

    xor eax, eax
    mov ax, [HFSPStartupFile+16]
    shl eax, 16
    xor edx, edx
    mov dx, [HFSPStartupFile+18]
    add eax, edx
    shl eax, 3
    mov dword [DAPstartblk], eax
    mov dword [DAPstartblk+2], 0

    mov si, DAPlen
    mov ah, 0x42
    mov dl, 0x80
    int 0x13
    jc KernLoadError      ; cf set on error, ah = error code

    mov al, 0x03
    out 0x60, al    ; enable A20 gate for memory >1MB

    call switch_to_pm
    jmp $ ; this will actually never be executed

BadHFSSignature:
    mov bx,msgHFSSigBad
    call print
    jmp $

KernLoadError:
    mov bx,msgKernLoadFail
    call print
    mov dl, ah
    xor dh, dh
    call printHex
    call printNL
    mov dx, [DAPblocks]   ; number of blocks read ok
    call printHex
    mov bx, msgBlocksRead
    call print
    jmp $

%include "data/strings.asm"
%include "data/hfsplus.asm"
%include "utilities/16bit/print.asm"
%include "utilities/16bit/disk.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
    mov ebx, msgProtMode
    call printStringPM ; Note that this will be written at the top left corner
    call kernAddr
    jmp $


; bootsector
times 510-($-$$) db 0
dw 0xaa55

; this code gets loaded to 0x7e00

%include "utilities/32bit/32bit-gdt.asm"
%include "utilities/32bit/32bit-print.asm"
%include "utilities/32bit/32bit-switch.asm"

DAP:
DAPlen      resb    1
DAPreserved resb    1
DAPblocks   resw    1
DAPbuffer   resd    1
DAPstartblk resq    1
DAPbuffer64 resq    1
