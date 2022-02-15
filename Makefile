SHELL = /bin/sh
LD = ld
OBJCOPY = objcopy
DD = dd
QEMU = qemu-system-i386
QEMUFLAGS = -fda $(MYKERNEL_IMG) -vga cirrus -d cpu_reset -d int -m 4G
export CFLAGS = \
	-O3 \
	-march=i386 \
	-mtune=i386 \
	-mgeneral-regs-only \
	-I$(shell pwd)/include \
	-m32 \
	-nostdinc \
	-nostdlib \
	-fomit-frame-pointer \
	-fno-stack-protector \
	-fno-asynchronous-unwind-tables \
	-fno-inline \
	-fno-pic \
	-fno-pie \
	-fno-unroll-loops \
	-fno-common \
	-ffreestanding \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-Wshadow \
	-W \
	-Wundef \
	-Wconversion \
	-Wpadded \
	-Werror \
	-Wno-error=unused-parameter \
	-Wno-error=unused-variable
LDFLAGS = -m elf_i386 -T setup.ld
OCFLAGS = -O binary
RM = rm -f
MYKERNEL_ELF = mykernel.elf
MYKERNEL_BIN = mykernel.bin
MYKERNEL_IMG = mykernel.img
SUBDIRS = boot kernel driver x86 misc mm

all:
	@for subdir in $(SUBDIRS); do \
		cd $$subdir && $(MAKE) all; \
		cd ..; \
	done
	$(LD) $(LDFLAGS) -o $(MYKERNEL_ELF)
	$(OBJCOPY) $(OCFLAGS) $(MYKERNEL_ELF) $(MYKERNEL_BIN) 
	$(DD) if=/dev/zero of=$(MYKERNEL_IMG) bs=1024 count=1440
	$(DD) if=$(MYKERNEL_BIN) of=$(MYKERNEL_IMG) conv=notrunc bs=512 seek=0

clean:
	@for subdir in $(SUBDIRS); do \
		cd $$subdir && $(MAKE) clean; \
		cd ..; \
	done
	$(RM) $(MYKERNEL_ELF) $(MYKERNEL_BIN) $(MYKERNEL_IMG)

run: all
	$(QEMU) $(QEMUFLAGS)

rundbg: all
	$(QEMU) $(QEMUFLAGS) -s -S

.PHONY: all, clean, run, rundbg
