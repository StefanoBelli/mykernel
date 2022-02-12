#include <x86/x86.h>
#include <x86/idt.h>
#include <x86/pic.h>
#include <x86/pit.h>
#include <driver/kbd.h>
#include <kernel/kvga.h>
#include <kernel/kprintf.h>
#include <kernel/isr.h>
#include <kernel/misc.h>
#include <misc/gcc.h>

typedef struct {
	udword base_low;
	udword base_high;
	udword length_low;
	udword length_high;
	udword type;
	udword reserved; // ACPI things
} packed memory_map_entry;

extern __mykapi void pgsetup_finalize();

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

__mykapi void log_memory_map() {
	udword n_ents = *(udword*) 0xffc07e00;
	memory_map_entry* map = (memory_map_entry*) 0xffc07e04;

	for(udword i = 0; i < n_ents; ++i) {
		kprintf("from %p to %p is %s\n", 
				map[i].base_low, 
				map[i].length_low + map[i].base_low - 1, 
				map[i].type == 1 ? "usable" : "reserved" );
	}
}

void kmain() {
	pgsetup_finalize();
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
	kprintf("BIOS-E820 provided memory map (rhs range next byte incl):\n");
	log_memory_map();
fail_halt:
	system_halt();
}
