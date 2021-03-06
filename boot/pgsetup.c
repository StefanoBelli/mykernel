#include <misc/gcc.h>
#include <x86/x86.h>
#include <boot/pgsetup.h>
#include <mm/pgtbl.h>

uint32_t* pd = (uint32_t*) 0xc0000000;

__mykapi void pgsetup_finalize() {
	/*
	 * Mark first page table in PDT as not present,
	 * this causes virtual addresses 0 .. 1023 * 4096
	 * not to be usable anymore.
	 *
	 * Page table (1) state, however, remains unchanged 
	 * as it is also "linked" to PDT entry #1023
	 */
	pd[0] = 2;

	/*
	 * Invalidate TLB-cache entries corresponding 
	 * to virtual addresses 0 .. 1023 * 4096
	 */
	for(uint32_t i = 0; i < 1024; ++i) {
		x86_invlpg(i << 12);
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
	for(uint32_t i = 256; i < 1024; ++i) {
		*((uint32_t*)0xc0001000 + i) = 2; //"bootstrap" page table
		x86_invlpg(0xffc00000 + (i << 12));
	}
}
/*
void pgsetup_extend_kernel_pages() {
	 * Extend kernel pages since we've left
	 * PT(2), which is the first kernel page table, maps
	 * 256 * 4096 .. (256 + 1023) * 4096
	 *
	 * Omitting 4096 factor (which is added later in physical
	 * frame address calculation), we restart filling KPTs from
	 * 1280 * 4096
	uint32_t start = 1280;
	
	for(uint32_t i = 0; i < 253; ++i) {
		 * Calculate next kernel page table virtual address
		 * since PT(3) maps frames to store page tables themselves
		 * in physical memory -- PDT[1022] = PT(3)
		uint32_t kpt_virt_addr = 0xff800000 + (i * 0x1000);
		
		 * Place next kernel page table physical address into PDT
		 * going from # 769 up to # 1021
		 * PDT[768] = KPT(0) = PT(2)
		 * PDT[769] = KPT(1)
		 * PDT[770] = KPT(2)
		 * ...
		 * PDT[1021] = KPT(252)
		*((uint32_t*)0xc0000000 + (769 + i)) = 3 | (0xbfc00000 + (i * 0x1000));

		for(uint32_t j = 0; j < 1024; ++j) {
			 * Fill next kernel page table with physical frames address
			 * for kernel data/code
			 * 
			 * restarts from 0x500000
			*((uint32_t*)kpt_virt_addr + j) = 3 | (0x1000 * (j + start));
		}
		
		start += 1024;
	}
}
*/
