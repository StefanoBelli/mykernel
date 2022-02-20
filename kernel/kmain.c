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
#include <mm/memmap.h>
#include <boot/pgsetup.h>

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

	kprintf("kernel: first init phase done\n");

	if(mm_memmap_seek() != 0) {
		kprintf("kernel: seeking available memory failed\n");
		kern_init_failure();
	}

	if (mm_memmap_ptstore_setup() != 0) {
		kprintf("kernel: not enough memory\n");
		kern_init_failure();
	}

	mm_memmap_log_avail_memory();

	uint32_t fralloc_init_fail = mm_fralloc_init();
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
		kprintf("kernel: kbd init failed (%d)\n", kbd_init_fail);
		kern_init_failure();
	}

	x86_pic_clear_mask(1);

	kprintf("kernel: final init phase done\n");

	system_halt();
}
