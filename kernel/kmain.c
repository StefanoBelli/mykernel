#include <x86/x86.h>
#include <x86/idt.h>
#include <x86/pic.h>
#include "kvga.h"
#include "kprintf.h"
#include "traps.h"
#include "irqs.h"

__mykapi void kvga_kprintf_init() {
	kvga_set_start_pos();
	kvga_cursor(0, 0);
}

__mykapi void kvga_kprintf_printer(const mykt_int_8* buf, mykt_uint_32 len) {
	kvga_write(
			buf, 
			VGA_TEXT_COLOR_BLACK, 
			VGA_TEXT_COLOR_WHITE, 
			len, 
			kvga_scroll
			);
}

void kmain() {
	x86_idt_install();
	x86_pic_remap();
	trap_gates_install();
	irq_gates_install();
	
	x86_sti();

	kprintf_init(kvga_kprintf_printer, kvga_kprintf_init);
	kprintf("kmain@%p: we're in protected mode!\n", kmain);
	kprintf("kmain@%p: kernel entry point reached\n", kmain);
	kprintf("kmain@%p: cpu halt\n", kmain);

	x86_cli();
	x86_hlt();
}
