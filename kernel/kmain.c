#include <x86/x86.h>
#include <x86/idt.h>
#include <x86/pic.h>
#include <x86/pit.h>
#include <driver/kbd.h>
#include "kvga.h"
#include "kprintf.h"
#include "ksleep.h"
#include "isr.h"
#include "misc.h"

__mykapi void kvga_kprintf_init() {
	kvga_set_start_pos();
	kvga_cursor(0, 0);
}

__mykapi void kvga_kprintf_printer(const byte* buf, udword len) {
	kvga_write(
			buf, 
			VGA_TEXT_COLOR_BLACK, 
			VGA_TEXT_COLOR_WHITE,
			len, 
			kvga_scroll
			);
}

/*
 * PDT phys = 0x100000, virt = 0xc0000000
 * bootstrap PT phys = 0x101000, virt = 0xc0001000
 * kernel PT phys = 0x102000, virt = 0xc0002000
 */
__mykapi void finalize_minimal_paging_setup() {
	*(udword*)0xc0000000 = 2;

	for(udword i = 0; i < 1024; ++i) {
		x86_invlpg(i * 4096);
	}

	for(udword i = 256; i < 1024; ++i) {
		*((udword*)0xc0001000 + i) = 2;
	}
}

void kmain() {
	finalize_minimal_paging_setup();
	x86_idt_install();
	x86_pic_remap();
	x86_pic_set_mask(0);
	x86_pic_set_mask(1);
	x86_pit_set_freq(1000);
	isr_set_int_gates();
	x86_sti(); //end init phase

	kprintf_init(kvga_kprintf_printer, kvga_kprintf_init);
	ksleep_init();

	dword kbd_init_fail = kbd_init();
	if(kbd_init_fail != 0) {
		kprintf("kbd init failed (%d)\n", kbd_init_fail);
		goto fail_halt;
	}

	x86_pic_clear_mask(1);

	kprintf("kernel basic initialization done\n");

fail_halt:
	system_halt();
}
