#include <misc/gcc.h>
#include <misc/string.h>
#include "x86.h"
#include "idt.h"

typedef struct {
	mykt_uint_16 offset_low;
	mykt_uint_16 cs;
	mykt_uint_8 reserved;
	mykt_uint_8 attrs;
	mykt_uint_16 offset_high;
} packed idt_entry;

typedef struct {
	mykt_uint_16 limit;
	mykt_uint_32 base;
} packed idt_desc;

static idt_entry idt[256];
static idt_desc idtd;

__mykapi void x86_idt_install() {
	idtd.limit = sizeof(idt) - 1;
	idtd.base = (mykt_uint_32) &idt[0];
	myk_memset(idt, 0, sizeof(idt));

	x86_lidt((mykt_uint_32) &idtd);
}

__mykapi void x86_set_int_gate(mykt_uint_8 m, mykt_uint_8 i, int_gate_fp g) {
	idt[i].offset_low = (mykt_uint_16) (((mykt_uint_32) g) & 0xffff);
	idt[i].cs = 8;
	idt[i].attrs = m;
	idt[i].offset_high = (mykt_uint_16) (((mykt_uint_32) g) >> 16);
}

