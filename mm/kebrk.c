#include <kernel/kprintf.h>
#include <mm/pgtbl.h>
#include <mm/fralloc.h>
#include <mm/kebrk.h>

#define KERNEL_INITIAL_BREAK_VA 0xc0400000

static uint32_t current_break = KERNEL_INITIAL_BREAK_VA; //incl
static uint32_t limit_break = 0; //excl

__mykapi void kebrk_init() {
	limit_break = __mm_fralloc_get_bitmap_va();
}

__mykapi void* kebrk() {
	if(unlikely((current_break + 4096) >= limit_break)) {
		return KEBRK_EXHAUSTED_MEMORY;
	}

	uint32_t cur_pde_idx = current_break >> 22;
	uint32_t cur_pte_idx = ((current_break & 0xffc00) >> 12) + 1;

	if(unlikely(cur_pte_idx == 1024)) {
		uint32_t i = 0;
		for(; i < 1024; ++i) {
			for(uint32_t j = 0; j < 1024; ++j) {
				if(!((pt + (i << 12))[j] & 1)) {
					break;
				}
			}
		}

		++cur_pde_idx;
		pd[cur_pde_idx] = (pt_phys + (i << 12)) | 3;
		cur_pte_idx = 0;
	}

	uint32_t frame_phys_addr = mm_fralloc_reserve();
	if(!FRALLOC_RESERVE_IS_OK(frame_phys_addr)) {
		kprintf("kebrk: fralloc failed, log entry follows\n");
		mm_fralloc_log_reserve_err(frame_phys_addr);
		return KEBRK_FRALLOC_FAILURE;
	}
	
	uint32_t *cur_pt = pt + ((pd[cur_pde_idx] - pt_phys) >> 12);
	cur_pt[cur_pte_idx] = (frame_phys_addr << 12) | 3;

	return (void*) (0x1000 | cur_pte_idx << 12 | cur_pde_idx << 22);
}
