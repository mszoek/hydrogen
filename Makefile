SYSTEM := $(shell uname -s)
DDFLAGS=
EXT=.exe

# Size of the hard disk image in 512-byte sectors (i.e. 10MB)
HDSIZE=20480

ifneq ($(findstring MINGW, $(SYSTEM)),MINGW)
	DDFLAGS=iflag=fullblock
	EXT=
endif

all: cleanup kernel.bin bootsect

boot: bootsect embedkernel
	@echo Installing bootsector to hd.img on $(SYSTEM) with $(DDFLAGS)
	cat bootsect.bin | dd $(DDFLAGS) conv=notrunc bs=512 count=2 of=hd.img
	fsck.hfsplus hd.img
	./embedkernel

embedkernel: embedkernel.c

image: bootsect
	@echo Building HD image on $(SYSTEM) with $(DDFLAGS)
	dd if=/dev/zero $(DDFLAGS) bs=512 count=$(HDSIZE) of=hd.img
	mkfs.hfsplus -v "H2OS HD" hd.img
	cat bootsect.bin | dd $(DDFLAGS) conv=notrunc bs=512 count=2 of=hd.img
	fsck.hfsplus hd.img

bootsect:
	nasm -f bin bootsect.asm -o bootsect.bin

%.o: %.c
	$(CC) -g -Iincludes -ffreestanding -m32 $(CFLAGS) -o $@ -c $<

%.o: %.asm
	nasm -f win32 -o $@ $<

KERNEL_OBJS=kernel.o kmem.o kstring.o idt.o isr.o drivers/video_ports.o drivers/screen.o drivers/keyboard.o interrupt.o

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
	rm -f bootsect.bin kernel.bin kernel.o
	rm -f kernel$(EXT) $(KERNEL_OBJS)
