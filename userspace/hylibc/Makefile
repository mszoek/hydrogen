CC64=gcc
CFLAGS=-g -Iincludes -I../../kernel/includes -nostdlib -ffreestanding -mno-red-zone -fstack-check=no -fstack-protector-explicit -fno-exceptions
LIB_SRCS=$(wildcard src/*.c)
LIB_OBJS=${LIB_SRCS:.c=.o}

all: clean libc.a

clean:
	rm -f libc.a $(LIB_OBJS)

libc.a: $(LIB_OBJS)
	ar crs libc.a $(LIB_OBJS)

%.o: %.c
	$(CC64) $(CFLAGS) -o $@ -c $<
