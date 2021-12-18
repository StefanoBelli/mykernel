#include <x86/idt.h>
#include <x86/pic.h>
#include <misc/string.h>
#include "isr.h"
#include "kprintf.h"
#include "misc.h"

typedef void (*final_isr_handler_fp)(interrupt_frame);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();

static final_isr_handler_fp final_handlers[256]; // 47..256 reserved for future usages

__mykapi void isr_set_int_gates() {
	x86_set_int_gate(IDT_EXCP, 0, isr0);
	x86_set_int_gate(IDT_EXCP, 1, isr1);
	x86_set_int_gate(IDT_EXCP, 2, isr2);
	x86_set_int_gate(IDT_EXCP, 3, isr3);
	x86_set_int_gate(IDT_EXCP, 4, isr4);
	x86_set_int_gate(IDT_EXCP, 5, isr5);
	x86_set_int_gate(IDT_EXCP, 6, isr6);
	x86_set_int_gate(IDT_EXCP, 7, isr7);
	x86_set_int_gate(IDT_EXCP, 8, isr8);
	x86_set_int_gate(IDT_EXCP, 9, isr9);
	x86_set_int_gate(IDT_EXCP, 10, isr10);
	x86_set_int_gate(IDT_EXCP, 11, isr11);
	x86_set_int_gate(IDT_EXCP, 12, isr12);
	x86_set_int_gate(IDT_EXCP, 13, isr13);
	x86_set_int_gate(IDT_EXCP, 14, isr14);
	x86_set_int_gate(IDT_EXCP, 15, isr15);
	x86_set_int_gate(IDT_EXCP, 16, isr16);
	x86_set_int_gate(IDT_EXCP, 17, isr17);
	x86_set_int_gate(IDT_EXCP, 18, isr18);
	x86_set_int_gate(IDT_EXCP, 19, isr19);
	x86_set_int_gate(IDT_EXCP, 20, isr20);
	x86_set_int_gate(IDT_EXCP, 21, isr21);
	x86_set_int_gate(IDT_EXCP, 22, isr22);
	x86_set_int_gate(IDT_EXCP, 23, isr23);
	x86_set_int_gate(IDT_EXCP, 24, isr24);
	x86_set_int_gate(IDT_EXCP, 25, isr25);
	x86_set_int_gate(IDT_EXCP, 26, isr26);
	x86_set_int_gate(IDT_EXCP, 27, isr27);
	x86_set_int_gate(IDT_EXCP, 28, isr28);
	x86_set_int_gate(IDT_EXCP, 29, isr29);
	x86_set_int_gate(IDT_EXCP, 30, isr30);
	x86_set_int_gate(IDT_EXCP, 31, isr31);
	x86_set_int_gate(IDT_IRQ, 32, isr32);
	x86_set_int_gate(IDT_IRQ, 33, isr33);
	x86_set_int_gate(IDT_IRQ, 34, isr34);
	x86_set_int_gate(IDT_IRQ, 35, isr35);
	x86_set_int_gate(IDT_IRQ, 36, isr36);
	x86_set_int_gate(IDT_IRQ, 37, isr37);
	x86_set_int_gate(IDT_IRQ, 38, isr38);
	x86_set_int_gate(IDT_IRQ, 39, isr39);
	x86_set_int_gate(IDT_IRQ, 40, isr40);
	x86_set_int_gate(IDT_IRQ, 41, isr41);
	x86_set_int_gate(IDT_IRQ, 42, isr42);
	x86_set_int_gate(IDT_IRQ, 43, isr43);
	x86_set_int_gate(IDT_IRQ, 44, isr44);
	x86_set_int_gate(IDT_IRQ, 45, isr45);
	x86_set_int_gate(IDT_IRQ, 46, isr46);
	x86_set_int_gate(IDT_IRQ, 47, isr47);
}

__mykapi void isr_set_final_handlers() {
	myk_memset(final_handlers, 0, sizeof(final_handlers));
}

void dont_optimize omit_frame_pointer isr_handler(interrupt_frame frame) {
	if(final_handlers[frame.intno]) {
		final_handlers[frame.intno](frame);
	} else {
		kprintf("unhandled isr, register status follows:\n");
		isr_log_interrupt_frame(frame);
		system_halt();
	}

	if(frame.intno > 31 && frame.intno < 48) {
		x86_pic_eoi((mykt_uint_8)frame.intno);
	}
}

void isr_log_interrupt_frame(interrupt_frame f) {
	kprintf("segment registers:\n"
			"\tcs = %p, ss = %p, gs = %p, fs = %p, es = %p, ds = %p\n"
			"general purpose registers:\n"
			"\teax = %p, ebx = %p, ecx = %p, edx = %p\n"
			"\tedi = %p, esi = %p, ebp = %p, esp = %p\n"
			"\tuseresp = %p\n"
			"instruction pointer:\n"
			"\teip = %p\n"
			"flags:\n"
			"\tefl = %p\n"
			"interrupt:\n"
			"\tno = %p, ec = %p\n",
			f.cs, f.ss, f.gs, f.fs, f.es, f.ds,
			f.eax, f.ebx, f.ecx, f.edx,
			f.edi, f.esi, f.ebp, f.esp,
			f.useresp,
			f.eip,
			f.efl,
			f.intno, f.ec);
}
