#include <misc/gcc.h>
#include <misc/string.h>
#include <x86/x86.h>
#include <x86/idt.h>

typedef struct {
	uint16_t offset_low;
	uint16_t cs;
	uint8_t reserved;
	uint8_t attrs;
	uint16_t offset_high;
} packed idt_entry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} packed idt_desc;

static idt_entry idt[256];
static idt_desc idtd;

__mykapi void x86_idt_install() {
	idtd.limit = sizeof(idt) - 1;
	idtd.base = (uint32_t) &idt[0];
	myk_memset(idt, 0, sizeof(idt));

	x86_lidt((uint32_t) &idtd);
}

__mykapi void x86_set_int_gate(uint8_t m, uint8_t i, int_gate_fp g) {
	idt[i].offset_low = (uint16_t) (((uint32_t) g) & 0xffff);
	idt[i].cs = 8;
	idt[i].attrs = m;
	idt[i].offset_high = (uint16_t) (((uint32_t) g) >> 16);
}

