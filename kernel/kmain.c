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

__mykapi void finalize_minimal_paging_setup() {
	/*
	 * Mark first page table in PDT as not present,
	 * this causes virtual addresses 0 .. 1023 * 4096
	 * not to be usable anymore.
	 *
	 * Page table (1) state, however, remains unchanged 
	 * as it is also "linked" to PDT entry #1023
	 */
	*(udword*)0xc0000000 = 2;

	/*
	 * Invalidate TLB-cache entries corresponding 
	 * to virtual addresses 0 .. 1023 * 4096
	 */
	for(udword i = 0; i < 1024; ++i) {
		x86_invlpg(i * 4096);
	}

	/*
	 * Page table (1) entries from 256 to 1023 marked as non-present
	 * because they would overlap frames with first kernel page table (2) 
	 *
	 * PT(1): 0 .. 256 * 4096 .. 1024 * 4096
	 * PT(2):      256 * 4096 .. 1024 * 4096 .. (256 + 1024) * 4096
	 *             ^^^^^^^^^^^^^^^^^^^^^^^^^
	 *             overlapping frames
	 *
	 * Even if none of the corresponding VAs (in conjunction with 
	 * PDT #1023 entry placement) were used to access memory, we still
	 * invalidate TLB-cache entries
	 */
	for(udword i = 256; i < 1024; ++i) {
		*((udword*)0xc0001000 + i) = 2;
		x86_invlpg(0xff800000 + (i * 4096));
	}
}

__mykapi void extend_kernel_pages() {
	/*
	 * Extend kernel pages since we've left
	 * PT(2), which is the first kernel page table, maps
	 * 256 * 4096 .. (256 + 1023) * 4096
	 *
	 * Omitting 4096 factor (which is added later in physical
	 * frame address calculation), we restart filling KPTs from
	 * 1280 * 4096
	 */
	udword start = 1280;
	
	for(udword i = 0; i < 253; ++i) {
		/*
		 * Calculate next kernel page table virtual address
		 * since PT(3) maps frames to store page tables themselves
		 * in physical memory -- PDT[1022] = PT(3)
		 */
		udword kpt_virt_addr = 0xff800000 + (i * 0x1000);
		
		/*
		 * Place next kernel page table physical address into PDT
		 * going from # 769 up to # 1021
		 * PDT[768] = KPT(0) = PT(2)
		 * PDT[769] = KPT(1)
		 * PDT[770] = KPT(2)
		 * ...
		 * PDT[1021] = KPT(252)
		 */
		*((udword*)0xc0000000 + (769 + i)) = 3 | (0xbfc00000 + (i * 0x1000));

		for(udword j = 0; j < 1024; ++j) {
			/*
			 * Fill next kernel page table with physical frames address
			 * for kernel data/code
			 * 
			 * restarts from 0x500000
			 */
			*((udword*)kpt_virt_addr + j) = 3 | (0x1000 * (j + start));
		}
		
		start += 1024;
	}
}

void kmain() {
	finalize_minimal_paging_setup();
	extend_kernel_pages();
	__asm__ __volatile__("movb $0xbe, 0xffcfffff;");
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
