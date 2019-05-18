CC64=gcc
CFLAGS=-g -D__hydrogen -D__STDC_NO_THREADS__ -Iincludes -nostdlib -nostdinc -ffreestanding -mno-red-zone -fstack-check=no -fstack-protector-explicit -fno-exceptions
LIB_SRCS=$(wildcard src/*.c)
LIB_OBJS=${LIB_SRCS:.c=.o}

all: clean libc.a

clean:
	rm -f libc.a $(LIB_OBJS)

prep:
	cp -fv ../../kernel/includes/syscalls.h includes/syscalls.h

libc.a: prep $(LIB_OBJS)
	ar crs libc.a $(LIB_OBJS)

%.o: %.c
	$(CC64) $(CFLAGS) -o $@ -c $<
