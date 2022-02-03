SHELL = /bin/sh
AS = as
RM = rm -f
ASFLAGS = --32
OBJS = boot.o head.o

all: $(OBJS)

$(OBJS): %.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

.PHONY: all, clean
