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
#include <mm/fralloc.h>

#define MIN_PHYS_MEM_AVAIL 0x100000

typedef struct {
	uint32_t base_low;
	uint32_t base_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
	uint32_t reserved; // ACPI things
} packed memory_map_entry;

static uint32_t avail_phys_mem_min;
static uint32_t avail_phys_mem_max;

uint32_t first_pt_phys;
uint32_t pt_ptstore[1024] aligned(4096);

extern __mykapi void pgsetup_finalize();

static __mykapi void kvga_kprintf_init() {
	kvga_set_start_pos();
	kvga_cursor(0, 0);
}

static __mykapi void kvga_kprintf_printer(const int8_t* buf, uint32_t len) {
	kvga_write(
			buf, 
			VGA_TEXT_COLOR_BLACK, 
			VGA_TEXT_COLOR_WHITE,
			len, 
			kvga_scroll
			);
}

static __mykapi void seek_available_memory_from_map() {
	uint32_t n_ents = *(uint32_t*) 0xffc07e00;
	memory_map_entry* map = (memory_map_entry*) 0xffc07e04;

	kprintf("memmap: got %u total entries\n", n_ents);

	for(uint32_t i = 0; i < n_ents; ++i) {
		char* typestr = "reserved";
		uint32_t max_mem = map[i].length_low + map[i].base_low - 1;
		if(map[i].type == 1) {
			typestr = "usable";
			if(map[i].base_low <= MIN_PHYS_MEM_AVAIL
					&& max_mem > avail_phys_mem_max) {
				avail_phys_mem_min = MIN_PHYS_MEM_AVAIL;
				avail_phys_mem_max = max_mem;
			}
		}

		kprintf("memmap: from %p to %p is %s\n", map[i].base_low, 
				max_mem, typestr);
	}
}

static __mykapi uint32_t setup_pages_for_ptstore() {
	uint32_t* pdt = (uint32_t*) 0xc0000000;
	uint32_t _pt_start = 1 + ((avail_phys_mem_max - 0x400000 - 1023) >> 12);
	
	first_pt_phys = _pt_start * 0x1000;

	pdt[1022] = ((uint32_t) pt_ptstore - 0xc0000000 + 0x100000) | 3;

	for(uint32_t i = 0; i < 1024; ++i) {
		pt_ptstore[i] = (_pt_start + i) * 0x1000 | 3;
	}

	avail_phys_mem_max -= 0x400000;
	
	return avail_phys_mem_max <= avail_phys_mem_min;
}

static __mykapi noinline void kern_init_failure() {
	kprintf("kernel: fatal error, unable to initialize!\n");
	while(1) {}
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
			"memory map (rhs range next int8_t incl):\n");
	
	seek_available_memory_from_map();
	if(avail_phys_mem_min != MIN_PHYS_MEM_AVAIL) {
		kprintf("kernel: seeking available memory failed\n");
		kern_init_failure();
	}

	avail_phys_mem_min += 0x400000;

	uint32_t pg_setup_ptstore_fail = setup_pages_for_ptstore();
	if (pg_setup_ptstore_fail != 0) {
		kprintf("kernel: not enough memory\n");
		kern_init_failure();
	}

	kprintf("kernel: after ptstore initialization\n"
			"kernel: total available memory - %u bytes\n"
			"kernel: total available memory - from %p to %p\n",
			avail_phys_mem_max - avail_phys_mem_min + 1, 
			avail_phys_mem_min, avail_phys_mem_max);

	uint32_t fralloc_init_fail = mm_fralloc_init(avail_phys_mem_min, avail_phys_mem_max);
	if(fralloc_init_fail != 0) {
		mm_fralloc_log_init_err(fralloc_init_fail);
		kern_init_failure();
	}

	kprintf("kernel: fralloc has complete control over physical memory\n");
	
	mm_fralloc_stats fralloc_stats = mm_fralloc_get_stats();
	mm_fralloc_log_stats(&fralloc_stats);

	kprintf("kernel: secondary init phase done\n");

	int32_t kbd_init_fail = kbd_init();
	if(kbd_init_fail != 0) {
		kprintf("kbd: init failed (%d)\n", kbd_init_fail);
		kern_init_failure();
	}

	x86_pic_clear_mask(1);

	kprintf("kernel: final init phase done\n");

	system_halt();
}
