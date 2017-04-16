SYSTEM := $(shell uname -s)
DDFLAGS=

ifneq ($(findstring MINGW, $(SYSTEM)),MINGW)
	DDFLAGS=iflag=fullblock
endif

all: bootsect infosect stage2 kernel.bin
	@echo Building HD image on $(SYSTEM) with $(DDFLAGS)
	cat bootsect.bin infosect.bin kernel.bin /dev/zero | dd $(DDFLAGS) bs=512 count=2880 of=hd.img

bootsect:
	nasm -f bin bootsect.asm -o bootsect.bin

mkinfosect: mkinfosect.c
	gcc -o mkinfosect mkinfosect.c

infosect: mkinfosect
	./mkinfosect

stage2: bootloader_s2.asm
	nasm -f bin bootloader_s2.asm -o bootloader_s2.bin

CFLAGS=-ffreestanding -m32
kernel.bin: kernel.c
	gcc $(CFLAGS) -o kernel.o -c kernel.c
#	ld -m elf_i386 -o kernel.bin -Ttext 0x0 --oformat binary kernel.o
	objcopy -O binary -j .text kernel.o kernel.bin
