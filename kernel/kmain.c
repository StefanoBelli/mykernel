#include <x86/x86.h>
#include "kvga.h"
#include "kprintf.h"

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
	kprintf_init(kvga_kprintf_printer, kvga_kprintf_init);
	/* buggy printf case */
	kprintf("kprintf is buggy\n");
	kprintf("cpu fault after this call\n");

	x86_cli();
	x86_hlt();
}
