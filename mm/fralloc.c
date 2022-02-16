#include <kernel/kprintf.h>
#include <mm/fralloc.h>

extern udword first_pt_phys;

static byte* frbitm;
static mm_fralloc_stats stats;

static __mykapi void* __init_bitmap_pagetable(
		udword pages, udword aligned_higher_addr) {
	udword* pdt = (udword*) 0xc0000000;
	udword* pt = (udword*) 0xff800000;

	pdt[1021] = 3  | first_pt_phys;
	
	udword _target = aligned_higher_addr >> 12;
	udword i = 1023;
	udword limit = 1023 - pages + 1;

	for(; i >= limit; --i) {
		pt[i] = 3 | (4096 * (_target + i));
	}

	return (void*) (0xff400000 | ((i + 1) << 12));
}

__mykapi mm_fralloc_stats mm_fralloc_get_stats() {
	return stats;
}

__mykapi void mm_fralloc_log_stats(const mm_fralloc_stats* s) {

}

__mykapi udword mm_fralloc_init(udword low_phys_addr, udword high_phys_addr) {
	if((low_phys_addr & 0xfff) != 0) {
		return FRALLOC_INIT_LOW_ALIGNMENT;
	}

	if((high_phys_addr & 0xfff) != 0xfff) {
		return FRALLOC_INIT_HIGH_LAST_BYTE;
	}

	if(low_phys_addr >= high_phys_addr) {
		return FRALLOC_INIT_ILLEGAL_ARGS;
	}

	udword high_phys_addr_aligned = high_phys_addr + 1;
	udword total_frames = (high_phys_addr_aligned - low_phys_addr) / 4096;
	udword pages_to_bitmap = (total_frames / 4096) + 1;

	if((pages_to_bitmap / 1024) >= 1) {
		return FRALLOC_INIT_TOO_MUCH_PAGES;
	}

	if((high_phys_addr - low_phys_addr) <= total_frames) {
		return FRALLOC_INIT_NOT_ENOUGH_MEMORY;
	}

	kprintf("total_frames = %u ;; diff = %u\n", total_frames, high_phys_addr - low_phys_addr);

	void* virtaddr = 
		__init_bitmap_pagetable(pages_to_bitmap, high_phys_addr_aligned);

	//INIT_STATS();
	//__init_frame_bitmap();
	
	return FRALLOC_INIT_OK;
}

__mykapi udword mm_fralloc_reserve() {
	return 0;
}

__mykapi udword mm_fralloc_release(udword phys) {
	return 0;
}
