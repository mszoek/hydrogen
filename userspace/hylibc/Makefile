CC64=gcc
CFLAGS=-g -D__hydrogen -D__STDC_NO_THREADS__ -D_PDCLIB_BUILD  -D_PDCLIB_STATIC_DEFINE -Iincludes -nostdlib -nostdinc -ffreestanding -mno-red-zone -fstack-check=no -fstack-protector-explicit -fno-exceptions
AS=as
ASFLAGS=
LIB_SRCS=$(wildcard src/*.c)
LIB_OBJS=${LIB_SRCS:.c=.o}

all: clean libc.a crt0.o crti.o crtn.o

clean:
	rm -f libc.a $(LIB_OBJS)

prep:
	cp -fv ../../kernel/includes/syscalls.h includes/syscalls.h

libc.a: prep $(LIB_OBJS)
	ar crs libc.a $(LIB_OBJS)

%.o: %.c
	$(CC64) $(CFLAGS) -o $@ -c $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ -s $<
