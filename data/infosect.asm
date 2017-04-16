; Define an "info sector" that contains locations for the 2nd stage loader
; The first stage loads this table from sector 2
; Zoe Knox 2017

ISMagic   db    'H2OS'   ; magic pattern of valid info sector

INFOSECTOR equ 0x8000
ISMarker      equ INFOSECTOR      ; 4 byte marker
ISStage2Start equ INFOSECTOR+4    ; starting sector of stage2 0-65535
ISStage2Len   equ ISStage2Start+2 ; length of stage2 in sectors
ISKernel      equ ISStage2Len+2   ; kernel filename, max 16 chars
