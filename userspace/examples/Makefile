CC=gcc
CFLAGS=-g -I../hylibc/includes -nostdlib -ffreestanding -mno-red-zone -fstack-check=no -fstack-protector-explicit -fno-exceptions
LDFLAGS=-nostdlib -ffreestanding -L../hylibc -Wl,--oformat=binary
LIBS=-lc

all: clean statkern.bin box.bin userfunc.bin hello.bin

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.bin: %.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)
