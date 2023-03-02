#include <kernel/kprintf.h>
#include <kernel/misc.h>
#include <mm/pgtbl.h>
#include <mm/fralloc.h>
#include <mm/kebrk.h>

#define KERNEL_INITIAL_BREAK_VA 0xc0400000
#define KERNEL_LIMIT_BREAK_VA 0xff400000

static uint32_t current_break = KERNEL_INITIAL_BREAK_VA;
static mm_kebrk_stats _g_stats;

__mykapi void mm_kebrk_init() {
	pd[KERNEL_INITIAL_BREAK_VA >> 22] = (pt_phys + 0x1000) | 3;
	_g_stats.good_calls = 0;
	_g_stats.total_calls = 0;
	_g_stats.lower_va = KERNEL_INITIAL_BREAK_VA;
	_g_stats.higher_va = KERNEL_LIMIT_BREAK_VA;
}

__mykapi void* mm_kebrk() {
	++_g_stats.total_calls;

	if(unlikely(current_break == KERNEL_LIMIT_BREAK_VA)) {
		return KEBRK_EXHAUSTED_MEMORY;
	}

	uint32_t frame_phys_addr = mm_fralloc_reserve();
	if(unlikely(!FRALLOC_RESERVE_IS_OK(frame_phys_addr))) {
		kprintf("kebrk: fralloc failed, log entry follows\n");
		mm_fralloc_log_reserve_err(frame_phys_addr);
		return KEBRK_FRALLOC_FAILURE;
	}

	uint32_t cur_pde_idx = current_break >> 22;
	uint32_t cur_pte_idx = (current_break & 0x3ff000) >> 12;
	
	uint32_t cur_pt = ((uint32_t) pt + 0x1000) + (((pd[cur_pde_idx] >> 12) - ((pt_phys + 0x1000) >> 12)) << 12);
	uint32_t *cur_pte = ((uint32_t*)cur_pt) + cur_pte_idx;

	if(*cur_pte & 1) {
		kprintf("kebrk: pte @ %p has present bit enabled, while expected it to be off\n", cur_pte);
		kernel_bug();
	}

	*cur_pte = (frame_phys_addr & 0xfffff000) | 3;

	void* ret_addr = (void*) (cur_pte_idx << 12 | cur_pde_idx << 22);

	if(unlikely(cur_pte_idx == 1023)) {
		uint32_t new_pt_idx = (pd[cur_pde_idx] >> 12) - ((pt_phys + 0x1000) >> 12) + 1;

		for(uint32_t j = 0; j < 1024; ++j) {
			uint32_t* pte = ((uint32_t*)(((uint32_t) pt) + 0x1000 + (new_pt_idx << 12))) + j;
			if(*pte & 1) {
				kprintf("kebrk: pte @ %p has present bit enabled, while expected it to be off\n", pte);
				kernel_bug();
			}
		}

		if(++cur_pde_idx < (KERNEL_LIMIT_BREAK_VA >> 22)) {
			uint32_t *pde = pd + cur_pde_idx;
			if(*pde & 1) {
				kprintf("kebrk: pde @ %p has present bit enabled, while expected it to be off\n", pde);
				kernel_bug();
			}
			pd[cur_pde_idx] = (pt_phys + 0x1000 + (new_pt_idx << 12)) | 3;
		}
		
		cur_pte_idx = 0;
	} else {
		++cur_pte_idx;
	}

	++_g_stats.good_calls;

	current_break = cur_pte_idx << 12 | cur_pde_idx << 22;

	return ret_addr;
}

__mykapi void mm_kebrk_log_err(void* r) {
	if(r == KEBRK_FRALLOC_FAILURE) {
		kprintf("kebrk: fralloc failure\n");
	} else if(r == KEBRK_EXHAUSTED_MEMORY) {
		kprintf("kebrk: exhausted memory\n");
	} else {
		kprintf("kebrk: success\n");
	}
}

__mykapi mm_kebrk_stats mm_kebrk_get_stats() {
	return _g_stats;
}

__mykapi void mm_kebrk_log_stats(const mm_kebrk_stats* s) {
	kprintf("kebrk_stats: %d good calls\n"
			"kebrk_stats: %d total calls\n"
			"kebrk_stats: extends from lower virtual address 0x%x\n"
			"kebrk_stats: extends to higher virtual address 0x%x\n",
			s->good_calls, s->total_calls, s->lower_va, s->higher_va);
}
