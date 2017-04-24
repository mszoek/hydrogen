SYSTEM := $(shell uname -s)
DDFLAGS=
EXT=.exe

ifneq ($(findstring MINGW, $(SYSTEM)),MINGW)
	DDFLAGS=iflag=fullblock
	EXT=
endif

all: cleanup bootsect infosect kernel.bin
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

.c.o:
	$(CC) -g -Iincludes -ffreestanding -m32 $(CFLAGS) -o $@ -c $<

KERNEL_OBJS=kernel.o kmem.o kstring.o idt.o isr.o drivers/video_ports.o drivers/screen.o drivers/keyboard.o

kernel.bin: $(KERNEL_OBJS)
ifneq ($(findstring MINGW, $(SYSTEM)),MINGW)
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 --oformat binary $(KERNEL_OBJS)
	ld -m elf_i386 -o kernel.elf -Ttext 0x1000 $(KERNEL_OBJS)
else
	ld -o kernel.exe -Ttext 0x1000 $(KERNEL_OBJS)
	objcopy -O binary kernel.exe kernel.bin
endif

debug: kernel.bin
	qemu-system-i386 -s -hda hd.img &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

cleanup:
	rm -f bootloader_s2.bin bootsect.bin infosect.bin kernel.bin kernel.o hd.img
	rm -f mkinfosect$(EXT) kernel.elf kernel.exe $(KERNEL_OBJS)
