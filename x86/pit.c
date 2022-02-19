#include <x86/x86.h>
#include <x86/pit.h>

__mykapi void x86_pit_set_freq(uint32_t fhz) {
	uint32_t d = 1193182 / fhz;
	x86_outb(0x43, 0x36);
	x86_outb(0x40, (int8_t) (d & 0xff));
	x86_outb(0x40, (int8_t) (d >> 8));
}

