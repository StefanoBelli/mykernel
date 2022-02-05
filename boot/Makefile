SHELL = /bin/sh
AS = as
RM = rm -f
ASFLAGS = --32
OBJS = $(patsubst %.S, %.o, $(wildcard *.S))

all: $(OBJS)

$(OBJS): %.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

.PHONY: all, clean
