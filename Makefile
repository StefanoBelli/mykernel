SHELL = /bin/sh
MAKE = make
LD = ld
OBJCOPY = objcopy
DD = dd
LDFLAGS = -m elf_i386 -T setup.ld
OCFLAGS = -O binary
RM = rm -f
MYKERNEL_ELF = mykernel.elf
MYKERNEL_BIN = mykernel.bin
MYKERNEL_IMG = mykernel.img
SUBDIRS = boot kernel x86

all:
	@for subdir in $(SUBDIRS); do \
		cd $$subdir; \
		$(MAKE) all; \
		cd ..; \
	done
	$(LD) $(LDFLAGS) -o $(MYKERNEL_ELF)
	$(OBJCOPY) $(OCFLAGS) $(MYKERNEL_ELF) $(MYKERNEL_BIN) 
	$(DD) if=/dev/zero of=$(MYKERNEL_IMG) bs=1024 count=1440
	$(DD) if=$(MYKERNEL_BIN) of=$(MYKERNEL_IMG) conv=notrunc bs=512 seek=0

clean:
	@for subdir in $(SUBDIRS); do \
		cd $$subdir; \
		$(MAKE) clean; \
		cd ..; \
	done
	$(RM) $(MYKERNEL_ELF) $(MYKERNEL_BIN) $(MYKERNEL_IMG)

.PHONY: all, clean
