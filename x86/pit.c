#include "x86.h"
#include "pit.h"

__mykapi void x86_pit_set_freq(mykt_uint_32 fhz) {
	mykt_uint_32 d = 1193182 / fhz;
	x86_outb(0x43, 0x36);
	x86_outb(0x40, (mykt_int_8) (d & 0xff));
	x86_outb(0x40, (mykt_int_8) (d >> 8));
}

