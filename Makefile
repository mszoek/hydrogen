SYSTEM := $(shell uname -s)
DDFLAGS=iflag=fullblock
NASM_ARCH=elf64 #elf32
# CC=i686-elf-gcc
# CXX=i686-elf-gcc
# AS=i686-elf-as
CC=gcc
CXX=gcc
AS=as
LD=ld
CC64=gcc
#CFLAGS=-g -Iincludes -m32 -nostdlib -ffreestanding -mno-red-zone -fno-exceptions
CFLAGS=-g -Iincludes -m64 -nostdlib -fstack-check=no -fstack-protector-explicit \
	-ffreestanding -mno-red-zone -fno-exceptions -mno-sse -mno-sse2 -mno-mmx
CXXFLAGS=$(CFLAGS) -fno-rtti -fpermissive -Wno-write-strings

# Size of the hard disk image in 512-byte sectors (i.e. 10MB)
HDSIZE=20480


all: clean kernel.bin mkiso

mkiso:
	cp -f kernel.bin iso/kernel.bin
	grub-mkrescue -o hydrogen.iso iso

boot: hd.img kernel.bin
	@echo Installing kernel.bin to hd.img on $(SYSTEM)
	sudo mount -o loop -t hfsplus hd.img /mnt
	sudo cp -fv kernel.bin /mnt
	sudo umount /mnt

image:
	$(MAKE) hd.img

hd.img: 
	@echo Building HD image on $(SYSTEM) with $(DDFLAGS)
	dd if=/dev/zero $(DDFLAGS) bs=512 count=$(HDSIZE) of=hd.img
	mkfs.hfsplus -v "H2OS HD" hd.img
	fsck.hfsplus hd.img

%.o: %.c
	$(CC) $(CFLAGS) -o $@.s -S $<
	$(AS) -o $@ $@.s
	rm -f $@.s

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@.s -S $<
	$(AS) -o $@ $@.s
	rm -f $@.s


%.o: %.asm
	nasm -f $(NASM_ARCH) -o $@ $<

KERNEL_SRC=$(wildcard kernel/*.cpp hw/*.cpp fs/*.cpp fonts/*.cpp)
KERNEL_INC=$(wildcard includes/*.h includes/hw/*.h includes/fs/*.h includes/fonts/*.h)
KERNEL_OBJ=kernel/loader.o ${KERNEL_SRC:.cpp=.o} hw/interrupt.o

kernel.bin: $(KERNEL_OBJ)
	ld -m elf_x86_64 -o kernel.bin -Tlinker.ld --oformat=elf64-x86-64 $(KERNEL_OBJ) 
#	ld -m elf_i386 -o kernel.bin -Tlinker.ld --oformat=elf32-i386 $(KERNEL_OBJ) 

debug: kernel.bin mkiso
	qemu-system-x86_64 -s -S -M q35 -accel tcg -drive file=hd.img,if=ide,media=disk -cdrom hydrogen.iso -boot d \
        -drive file=/usr/share/ovmf/x64/OVMF_CODE.fd,if=pflash,format=raw,unit=0,readonly=on &
	sleep 3
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.bin"

run: kernel.bin mkiso
	qemu-system-x86_64 -M q35 -accel kvm -drive file=hd.img,if=ide,media=disk -cdrom hydrogen.iso -boot d \
        -drive file=/usr/share/ovmf/x64/OVMF_CODE.fd,if=pflash,format=raw,unit=0,readonly=on 

clean:
	rm -f bootsect.bin kernel.bin kernel.o
	rm -f kernel.elf $(KERNEL_OBJ)
	find . -name \*.o.s -exec rm {} \;
