; Kernel loader stub to get the right entry point from bootloader
; This object must be linked first at 0x1000!
; Zoe Knox 2017

global _start
extern kernelMain
;extern _init

_start:
;		call	_init
		call 	kernelMain

		cli
die:		hlt
		jmp die
