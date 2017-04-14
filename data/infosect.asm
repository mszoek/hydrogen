; Define an "info sector" that contains locations for the 2nd stage loader
; The first stage loads this table from sector 2
; Zoe Knox 2017

ISMagic   db    'H2OS'   ; magic pattern of valid info sector

INFOSECTOR:
ISMarker      resb 4      ; 4 byte marker
ISStage2Start resw 1      ; starting sector of stage2 0-65535
ISStage2Len   resw 1      ; length of stage2 in sectors
ISKernel      resb 16     ; kernel filename, max 16 chars
