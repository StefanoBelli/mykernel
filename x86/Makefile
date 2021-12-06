SHELL = /bin/sh
CC = gcc
RM = rm -f
CFLAGS = -I.. -fno-asynchronous-unwind-tables -nostdinc -nostdlib -m32 -fno-pic -fno-pie -ffreestanding -std=c99 -pedantic -Wall -Wextra -W -Werror
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJS)

clean:
	$(RM) $(OBJS)

.PHONY: all, clean
