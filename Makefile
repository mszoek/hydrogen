SYSTEM := $(shell uname -s)
DDFLAGS=iflag=fullblock
NASM_ARCH=elf32
CC=i686-elf-gcc
CXX=i686-elf-gcc
AS=i686-elf-as
LD=ld
CC64=gcc
CFLAGS=-g -Iincludes -m32 -nostdlib -ffreestanding -mno-red-zone -fno-exceptions
CXXFLAGS=$(CFLAGS) -fno-rtti -fpermissive -Wno-write-strings

# Size of the hard disk image in 512-byte sectors (i.e. 10MB)
HDSIZE=20480


all: clean kernel.bin mkiso

mkiso:
	cp -f kernel.bin iso/kernel.bin
	grub-mkrescue -o hydrogen.iso iso

boot: bootsect kernel.bin embedkernel
	@echo Installing kernel.bin to hd.img on $(SYSTEM)
	sudo mount -o loop -t hfsplus hd.img /a
	sudo umount /a
	@echo Installing bootsector to hd.img on $(SYSTEM) with $(DDFLAGS)
	cat bootsect.bin | dd $(DDFLAGS) conv=notrunc bs=512 count=2 of=hd.img
	fsck.hfsplus hd.img
	./embedkernel

embedkernel: embedkernel.c
	$(CC64) -o $@ -Iincludes embedkernel.c

image: bootsect
	@echo Building HD image on $(SYSTEM) with $(DDFLAGS)
	dd if=/dev/zero $(DDFLAGS) bs=512 count=$(HDSIZE) of=hd.img
	mkfs.hfsplus -v "H2OS HD" hd.img
	cat bootsect.bin | dd $(DDFLAGS) conv=notrunc bs=512 count=2 of=hd.img
	fsck.hfsplus hd.img

bootsect:
	nasm -f bin bootsect.asm -o bootsect.bin

%.o: %.c
	$(CC) $(CFLAGS) -o $@.s -S $<
	$(AS) -o $@ $@.s

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@.s -S $<
	$(AS) -o $@ $@.s


%.o: %.asm
	nasm -f $(NASM_ARCH) -o $@ $<

KERNEL_SRC=$(wildcard kernel/*.cpp drivers/*.cpp hw/*.cpp)
KERNEL_INC=$(wildcard includes/*.h includes/hw/*.h includes/drivers/*.h)
KERNEL_OBJ=kernel/loader.o ${KERNEL_SRC:.cpp=.o} hw/interrupt.o

kernel.bin: $(KERNEL_OBJ)
	ld -m elf_i386 -o kernel.bin -Tlinker.ld $(KERNEL_OBJ) 

debug: kernel.bin
	qemu-system-i386 -s -hda hd.img &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	rm -f bootsect.bin kernel.bin kernel.o
	rm -f kernel.elf $(KERNEL_OBJ)
	find . -name \*.o.s -exec rm {} \;
