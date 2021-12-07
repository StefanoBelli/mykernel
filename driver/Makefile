SHELL = /bin/sh
CC = gcc
RM = rm -f
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJS)

clean:
	$(RM) $(OBJS)

.PHONY: all, clean
