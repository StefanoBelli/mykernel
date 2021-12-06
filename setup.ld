OUTPUT_FORMAT("elf32-i386")

SECTIONS {
	
	.text 0x7c00 : AT (0) {
		boot/boot.o (.text)
	}

	kernel.text 0x100000 : AT (0x200) {
		kernel/kmain.o (.text)
		x86/x86.o (.text)
	}

	kernel.data 0x200000 : AT (0x100200) {
		kernel/kmain.o (.data)
		kernel/kmain.o (.bss)
	}

	/DISCARD/ : {
		*(.note.gnu.property) 
	}

}

