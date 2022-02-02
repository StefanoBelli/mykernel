#include <misc/gcc.h>
#include <misc/string.h>
#include "x86.h"
#include "idt.h"

typedef struct {
	uword offset_low;
	uword cs;
	ubyte reserved;
	ubyte attrs;
	uword offset_high;
} packed idt_entry;

typedef struct {
	uword limit;
	udword base;
} packed idt_desc;

static idt_entry idt[256];
static idt_desc idtd;

__mykapi void x86_idt_install() {
	idtd.limit = sizeof(idt) - 1;
	idtd.base = (udword) &idt[0];
	myk_memset(idt, 0, sizeof(idt));

	x86_lidt((udword) &idtd);
}

__mykapi void x86_set_int_gate(ubyte m, ubyte i, int_gate_fp g) {
	idt[i].offset_low = (uword) (((udword) g) & 0xffff);
	idt[i].cs = 8;
	idt[i].attrs = m;
	idt[i].offset_high = (uword) (((udword) g) >> 16);
}

