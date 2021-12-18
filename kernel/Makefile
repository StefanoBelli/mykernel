SHELL = /bin/sh
CC = gcc
AS = as
ASFLAGS = --32
RM = rm -f
OBJS = $(patsubst %.c, %.o, $(wildcard *.c)) isr_stub.o

all: $(OBJS)

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS) $(OBJAS)

.PHONY: all, clean
