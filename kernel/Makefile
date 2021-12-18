SHELL = /bin/sh
CC = gcc
AS = as
ASFLAGS = --32
RM = rm -f
OBJS = $(patsubst %.S, %.o, $(wildcard *.S)) \
	   $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJS)

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

.PHONY: all, clean
