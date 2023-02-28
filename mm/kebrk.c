#include <kernel/kprintf.h>
#include <mm/pgtbl.h>
#include <mm/fralloc.h>
#include <mm/kebrk.h>
#include <x86/x86.h>

#define KERNEL_INITIAL_BREAK_VA 0xc0400000
#define KERNEL_LIMIT_BREAK_VA 0xff400000

static uint32_t current_break = KERNEL_INITIAL_BREAK_VA;

__mykapi void kebrk_init() {
	pd[KERNEL_INITIAL_BREAK_VA >> 22] = (pt_phys + 0x1000) | 3;
}

__mykapi void* kebrk() {
	if(unlikely((current_break + 4096) > KERNEL_LIMIT_BREAK_VA)) {
		return KEBRK_EXHAUSTED_MEMORY;
	}

	uint32_t cur_pde_idx = current_break >> 22;
	int32_t cur_pte_idx = ((current_break & 0x3ff000) >> 12);

	if(unlikely(cur_pte_idx == 1023)) {
		int32_t new_pt_idx = ((int32_t)pd[cur_pde_idx] >> 12) - (((int32_t)pt_phys + 0x1000) >> 12) + 1;

		for(uint32_t j = 0; j < 1024; ++j) {
			if(((uint32_t*)((uint32_t)(pt + 0x1000) + ((uint32_t)new_pt_idx << 12)))[j] & 1) {
				new_pt_idx = -1;
				break;
			}
		}

		if(new_pt_idx == -1) {
			kprintf("kebrk: KERNEL BUG - getting trapped\n");
			x86_int3();
		}

		pd[++cur_pde_idx] = (pt_phys + 0x1000 + ((uint32_t)new_pt_idx << 12)) | 3;
		cur_pte_idx = 0;
	}

	uint32_t frame_phys_addr = mm_fralloc_reserve();
	if(!FRALLOC_RESERVE_IS_OK(frame_phys_addr)) {
		kprintf("kebrk: fralloc failed, log entry follows\n");
		mm_fralloc_log_reserve_err(frame_phys_addr);
		return KEBRK_FRALLOC_FAILURE;
	}

	uint32_t cur_pt = ((uint32_t) pt + 0x1000) + (((pd[cur_pde_idx] >> 12) - ((pt_phys + 0x1000) >> 12)) << 12);
	((uint32_t*)cur_pt)[cur_pte_idx++] = (frame_phys_addr & 0xfffff000) | 3;

	return (void*) ((current_break = ((uint32_t) cur_pte_idx) << 12 | cur_pde_idx << 22) - 0x1000);
}
