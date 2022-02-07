OUTPUT_FORMAT("elf32-i386")

SECTIONS {
	
	boot.text 0x7c00 : AT (0) {
		boot/boot.o (.text)
	}

	kernel.headtext 0x100000 : AT(0x200) {
		boot/head.o (.text)
	}

	kernel.text /*virt=*/ 0xc000401d : AT (0x421d) {
		kernel/kmain.o (.text)
		kernel/kvga.o (.text)
		kernel/kprintf.o (.text)
		kernel/isr.o (.text)
		kernel/isr_stub.o (.text)
		kernel/misc.o (.text)
		kernel/excps.o (.text)
		kernel/ksleep.o (.text)
		driver/vga.o (.text)
		driver/kbd.o (.text)
		x86/x86.o (.text)
		x86/idt.o (.text)
		x86/pic.o (.text)
		x86/pit.o (.text)
		misc/itoa.o (.text)
		misc/string.o (.text)
	}

	/DISCARD/ : {
		*(.note.gnu.property) 
	}

}

