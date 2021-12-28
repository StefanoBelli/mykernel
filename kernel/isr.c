#include <x86/idt.h>
#include <x86/pic.h>
#include <misc/string.h>
#include "isr.h"
#include "kprintf.h"
#include "misc.h"
#include "excps.h"

#define ISR_START_EXCP 0
#define ISR_START_IRQ 32
#define N_ISR 48
#define MAX_INTS 256

typedef void (*entry_isr_handler_fp)();

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

static isrh_fp final_handlers[MAX_INTS] = {
	[1] = excp_debug,
	[3] = excp_breakpoint,
};

static const entry_isr_handler_fp entry_handlers[N_ISR] = {
	 isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,  isr8,  isr9, 
	isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19, 
	isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29, 
	isr30, isr31, isr32, isr33, isr34, isr35, isr36, isr37, isr38, isr39, 
	isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47
};

static const mykt_int_8* isr_name[N_ISR] = {
	"divide by zero exception","debug exception","nmi exception",
	"breakpoint exception","overflow exception","bound range exceeded exception",
	"invalid opcode exception","device not available exception","double fault exception",
	"coprocessor segment overrun exception","invalid tss exception","segment not present exception",
	"stack-segment fault exception","general protection fault exception","page fault exception",
	"reserved exception","x87 floating point exception","alignment check exception",
	"machine check exception","reserved exception","reserved exception", 
	"reserved exception","reserved exception","reserved exception", 
	"reserved exception","reserved exception","reserved exception", 
	"reserved exception","reserved exception","reserved exception", 
	"reserved exception","reserved exception","timer irq",						
	"keyboard irq","slave pic reserved irq","com2/com4 irq",						
	"com1/com3 irq","parallel port irq","floppy disk controller irq",
	"parallel port irq","rtc irq","irq2 redirect irq",
	"unassigned irq","unassigned irq","ps/2 mouse irq",
	"math coprocessor irq","primary ide channel irq","secondary ide channel irq"
};

__mykapi void isr_set_int_gates() {
	for(mykt_uint_8 i = ISR_START_EXCP; i < ISR_START_IRQ; ++i) {
		x86_set_int_gate(IDT_EXCP, i, entry_handlers[i]);
	}
	
	for(mykt_uint_8 i = ISR_START_IRQ; i < N_ISR; ++i) {
		x86_set_int_gate(IDT_IRQ, i, entry_handlers[i]);
	}
}

void dont_optimize omit_frame_pointer isr_handler(interrupt_frame frame) {
	if(final_handlers[frame.intno]) {
		final_handlers[frame.intno](frame);
	} else {
		kprintf("unhandled int, register status follows:\n");
		isr_log_interrupt_frame(frame);
		system_halt();
	}

	if(frame.intno >= ISR_START_IRQ && frame.intno < N_ISR) {
		x86_pic_eoi((mykt_uint_8) frame.intno - ISR_START_IRQ);
	}
}

void isr_log_interrupt_frame(interrupt_frame f) {
	kprintf(
			"segment registers:\n"
			"\tcs = %p, ss = %p, gs = %p, fs = %p, es = %p, ds = %p\n"
			"general purpose registers:\n"
			"\teax = %p, ebx = %p, ecx = %p, edx = %p\n"
			"\tedi = %p, esi = %p, ebp = %p, esp = %p\n"
			"\tuseresp = %p\n"
			"instruction pointer:\n"
			"\teip = %p\n"
			"flags:\n"
			"\tefl = %p\n"
			"interrupt(%s):\n"
			"\tno = %p, ec = %p\n",
			f.cs, f.ss, f.gs, f.fs, f.es, f.ds,
			f.eax, f.ebx, f.ecx, f.edx,
			f.edi, f.esi, f.ebp, f.esp,
			f.useresp,
			f.eip,
			f.efl,
			isr_name[f.intno], f.intno, f.ec
		);
}

__mykapi void isr_register_irq_handler(irqn i, isrh_fp h) {
	final_handlers[i + ISR_START_IRQ] = h;
}
