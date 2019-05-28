LIBC=../hylibc
CC=gcc
CFLAGS=-g -I../hylibc/includes -nostdlib -ffreestanding -mno-red-zone -fstack-check=no -fstack-protector-explicit -fno-exceptions
LIBS=-lc
LD=ld
LDFLAGS=-Tlinker.ld -L$(LIBC) -e_start
CRTI=$(LIBC)/crti.o
CRTN=$(LIBC)/crtn.o
CRT0=$(LIBC)/crt0.o

all: distclean gettime.bin statkern.bin box.bin userfunc.bin hello.bin

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin *.elf

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.bin: %.o
	$(LD) --oformat=binary $(LDFLAGS) -o $@ $(CRT0) $(CRTI) $< $(LIBS) $(CRTN)

%.elf: %.o
	$(LD) $(LDFLAGS) -o $@ $(CRT0) $(CRTI) $< $(LIBS) $(CRTN)

