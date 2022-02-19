#include <x86/x86.h>

__mykapi void x86_outb(int16_t port, int8_t data) {
	__asm__ ("outb %0, %1;" :: "a"(data), "Nd"(port));
}

__mykapi int8_t x86_inb(int16_t port) {
	int8_t out;
	__asm__ ("inb %1, %0;" : "=a"(out) : "Nd"(port));
	
	return out;
}
