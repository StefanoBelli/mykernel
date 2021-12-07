#include "x86.h"

void x86_outb(mykt_int_16 port, mykt_int_8 data) {
	__asm__ ("outb %0, %1;" :: "r"(data), "r"(port));
}

mykt_int_8 x86_inb(mykt_int_16 port) {
	mykt_int_8 out;
	__asm__ ("inb %1, %0;" : "=a"(out) : "Nd"(port));
	
	return out;
}
