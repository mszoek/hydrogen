SYSTEM := $(shell uname -s)
DDFLAGS=iflag=fullblock
NASM_ARCH=elf64
CC=gcc
CXX=gcc
AS=as
LD=ld
CC64=gcc
CFLAGS=-g -Ikernel/includes -m64 -nostdlib -fstack-check=no -fstack-protector-explicit \
	-ffreestanding -mno-red-zone -fno-exceptions -mno-sse -mno-sse2 -mno-mmx
CXXFLAGS=$(CFLAGS) -fno-rtti -fpermissive -Wno-write-strings

# Figure out if we are running in Windows Subssystem for Linux or native Linux
WSL := $(shell uname -a|grep -c Microsoft)
ifeq ($(WSL),1)
	ACCEL=tcg
	EXE=.exe
	OVMF='C:/Program Files/qemu/ovmf-x64/OVMF_CODE-pure-efi.fd'
else
	ACCEL=kvm
	OVMF=/usr/share/ovmf/x64/OVMF_CODE.fd
endif

# Size of the hard disk image in 512-byte sectors (i.e. 10MB)
HDSIZE=20480


all: clean kernel.bin mkiso libc bin

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

KERNEL_SRC=$(wildcard kernel/*.cpp kernel/hw/*.cpp kernel/fs/*.cpp kernel/fonts/*.cpp)
KERNEL_ASMSRC=$(wildcard kernel/switchtask.asm kernel/switchring3.asm)
KERNEL_INC=$(wildcard includes/*.h includes/hw/*.h includes/fs/*.h includes/fonts/*.h)
KERNEL_OBJ=kernel/loader.o ${KERNEL_SRC:.cpp=.o} ${KERNEL_ASMSRC:.asm=.o} kernel/hw/interrupt.o

kernel.bin: $(KERNEL_OBJ)
	ld -m elf_x86_64 -o kernel.bin -Tlinker.ld --no-relax $(KERNEL_OBJ) -Map kernel.map

debug: kernel.bin mkiso
	qemu-system-x86_64$(EXE) -s -S -M q35 -accel tcg -drive file=hd.img,if=ide,media=disk -cdrom hydrogen.iso -boot d \
        -drive file=$(OVMF),if=pflash,format=raw,unit=0,readonly=on -m 512m &
	sleep 2
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.bin" -ex "b breakpoint()"

run: kernel.bin mkiso
	qemu-system-x86_64$(EXE) -M q35 -accel $(ACCEL) -drive file=hd.img,if=ide,media=disk -cdrom hydrogen.iso -boot d \
        -drive file=$(OVMF),if=pflash,format=raw,unit=0,readonly=on -m 512m

clean:
	rm -f bootsect.bin kernel.bin kernel.o
	rm -f kernel.elf $(KERNEL_OBJ)
	find . -name \*.o.s -exec rm {} \;

libc:
	$(MAKE) -C userspace/hylibc

examples:
	$(MAKE) -C userspace/examples

bin:
	$(MAKE) -C userspace/bin
