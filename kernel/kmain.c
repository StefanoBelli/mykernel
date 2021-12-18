#include <x86/x86.h>
#include <x86/idt.h>
#include <x86/pic.h>
#include "kvga.h"
#include "kprintf.h"
#include "isr.h"
#include "misc.h"

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
	isr_set_int_gates();
	kprintf_init(kvga_kprintf_printer, kvga_kprintf_init);
	x86_sti(); //end init phase
	
	kprintf("kernel basic initialization done\n");

	system_halt();
}
