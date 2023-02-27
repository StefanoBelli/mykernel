#include <kernel/kprintf.h>
#include <mm/pgtbl.h>
#include <mm/fralloc.h>
#include <mm/kebrk.h>
#include <x86/x86.h>

#define KERNEL_INITIAL_BREAK_VA 0xc0400000

static uint32_t current_break = KERNEL_INITIAL_BREAK_VA; //incl
static uint32_t limit_break = 0; //excl

__mykapi void kebrk_init() {
	limit_break = __mm_fralloc_get_bitmap_va();
	pd[KERNEL_INITIAL_BREAK_VA >> 22] = pt_phys | 3;
}

__mykapi void* kebrk() {
	if(unlikely((current_break + 4096) >= limit_break)) {
		return KEBRK_EXHAUSTED_MEMORY;
	}

	uint32_t cur_pde_idx = current_break >> 22;
	int32_t cur_pte_idx = ((current_break & 0x3ff000) >> 12);

	if(unlikely(cur_pte_idx == 1023)) {
		int32_t new_pt_idx = ((int32_t)pd[cur_pde_idx] >> 12) - ((int32_t)pt_phys >> 12) + 1;

		for(uint32_t j = 0; j < 1024; ++j) {
			if(((uint32_t*)((uint32_t)pt + ((uint32_t)new_pt_idx << 12)))[j] & 1) {
				new_pt_idx = -1;
				break;
			}
		}

		if(new_pt_idx == -1) {
			kprintf("kebrk: kernel bug, system shall halt now\n");
			x86_int3();
		}


		pd[++cur_pde_idx] = (pt_phys + ((uint32_t)new_pt_idx << 12)) | 3;
		cur_pte_idx = -1;
	}

	uint32_t frame_phys_addr = mm_fralloc_reserve();
	if(!FRALLOC_RESERVE_IS_OK(frame_phys_addr)) {
		kprintf("kebrk: fralloc failed, log entry follows\n");
		mm_fralloc_log_reserve_err(frame_phys_addr);
		return KEBRK_FRALLOC_FAILURE;
	}

	uint32_t cur_pt = ((uint32_t) pt) + (((pd[cur_pde_idx] >> 12) - (pt_phys >> 12)) << 12);
	((uint32_t*)cur_pt)[++cur_pte_idx] = (frame_phys_addr << 12) | 3;

	return (void*) (current_break = ((uint32_t) cur_pte_idx) << 12 | cur_pde_idx << 22);
}
