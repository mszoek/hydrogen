SYSTEM := $(shell uname -s)
DDFLAGS=

ifneq ($(findstring MINGW, $(SYSTEM)),MINGW)
	DDFLAGS=iflag=fullblock
endif

all: bootsect
	echo Building HD image on $(SYSTEM) with $(DDFLAGS)
	cat bootsect.bin /dev/zero | dd $(DDFLAGS) bs=512 count=2880 of=hd.img

bootsect:
	nasm -f bin bootsect.asm -o bootsect.bin

loader.bin: loader.asm
	nasm -f bin loader.asm -o loader.bin

CFLAGS=-fno-builtin -O0 -nostartfiles -nostdlib -nodefaultlibs -static
kernel.bin: kernel.c loader.bin
	gcc $(CFLAGS) -o kernel.bin kernel.c
	cat loader.bin kernel.bin > kernel
