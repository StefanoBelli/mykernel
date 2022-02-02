#include "x86.h"

__mykapi void x86_outb(word port, byte data) {
	__asm__ ("outb %0, %1;" :: "a"(data), "Nd"(port));
}

__mykapi byte x86_inb(word port) {
	byte out;
	__asm__ ("inb %1, %0;" : "=a"(out) : "Nd"(port));
	
	return out;
}
