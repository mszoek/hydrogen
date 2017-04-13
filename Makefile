all: bootsect
	cat bootsect.bin kernel.bin /dev/zero | dd iflag=fullblock bs=512 count=2880 of=hd.img

bootsect:
	nasm -f bin bootsect.asm -o bootsect.bin

loader.bin: loader.asm
	nasm -f bin loader.asm -o loader.bin

CFLAGS=-fno-builtin -O0 -nostartfiles -nostdlib -nodefaultlibs -static
kernel.bin: kernel.c loader.bin
	gcc $(CFLAGS) -o kernel.bin kernel.c
	cat loader.bin kernel.bin > kernel
