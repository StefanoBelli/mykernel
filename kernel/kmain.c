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

#define MIN_PHYS_MEM_AVAIL 0x100000

typedef struct {
	udword base_low;
	udword base_high;
	udword length_low;
	udword length_high;
	udword type;
	udword reserved; // ACPI things
} packed memory_map_entry;

static udword avail_phys_mem_min;
static udword avail_phys_mem_max;

static udword pt_ptstore[1024] aligned(4096);

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

__mykapi void seek_available_memory_from_map() {
	udword n_ents = *(udword*) 0xffc07e00;
	memory_map_entry* map = (memory_map_entry*) 0xffc07e04;

	kprintf("memory map: got %u total entries\n", n_ents);

	for(udword i = 0; i < n_ents; ++i) {
		char* typestr = "reserved";
		udword max_mem = map[i].length_low + map[i].base_low - 1;
		if(map[i].type == 1) {
			typestr = "usable";
			if(map[i].base_low <= MIN_PHYS_MEM_AVAIL
					&& max_mem > avail_phys_mem_max) {
				avail_phys_mem_min = MIN_PHYS_MEM_AVAIL;
				avail_phys_mem_max = max_mem;
			}
		}

		kprintf("memory map: from %p to %p is %s\n", map[i].base_low, 
				max_mem, typestr);
	}
}

__mykapi void setup_pages_for_ptstore() {
	udword* pdt = (udword*) 0xc0000000;
	udword _pt_start = 1 + ((avail_phys_mem_max - 0x400000 - 1023) >> 12);

	pdt[1022] = ((udword) pt_ptstore - 0xc0000000 + 0x100000) | 3;

	for(udword i = 0; i < 1024; ++i) {
		pt_ptstore[i] = (_pt_start + i) * 0x1000 | 3;
	}

	avail_phys_mem_max -= 0x400000;
}

#define kern_log_avail_mem() { \
	kprintf("kernel: total available memory - %u bytes\n" \
			"kernel: total available memory - from %p to %p\n", \
			avail_phys_mem_max - avail_phys_mem_min + 1, \
			avail_phys_mem_min, avail_phys_mem_max); \
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

	kprintf("kernel: first init phase done\n"
			"bios-e820: provides the following "
			"memory map (rhs range next byte incl):\n");
	
	seek_available_memory_from_map();
	if(avail_phys_mem_min != MIN_PHYS_MEM_AVAIL) {
		kprintf("kernel: seeking available memory failed\n");
		goto fail_halt;
	}

	kern_log_avail_mem();

	setup_pages_for_ptstore();

	kprintf("kernel: secondary init phase done\n");
	kern_log_avail_mem();

	dword kbd_init_fail = kbd_init();
	if(kbd_init_fail != 0) {
		kprintf("kbd init failed (%d)\n", kbd_init_fail);
		goto fail_halt;
	}

	x86_pic_clear_mask(1);

	kprintf("kernel: final init phase done\n");
	kern_log_avail_mem();

fail_halt:
	system_halt();
}
