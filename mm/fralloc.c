#include <kernel/kprintf.h>
#include <mm/pgtbl.h>
#include <mm/fralloc.h>

#define ALLOCATOR_BUSY_FRAME ((int8_t) 0xfe)
#define REGULAR_BUSY_FRAME ((int8_t) 0xff)

extern __mykapi uint32_t __mm_memmap_get_avail_phys_mem_min();
extern __mykapi uint32_t __mm_memmap_get_avail_phys_mem_max();

static int8_t* frbitm;
static mm_fralloc_stats stats;

static __mykapi void* __init_bitmap_pagetable(uint32_t pages, 
		uint32_t aligned_higher_addr) {
	pd[1021] = 3 | pt_phys;

	uint32_t _target = aligned_higher_addr >> 12;
	uint32_t i = 1023;
	uint32_t limit = 1023 - pages + 1;

	for(; i >= limit; --i) {
		pt[i] = 3 | ((_target + i) << 12);
	}

	return (void*) (0xff400000 | ((i + 1) << 12));
}

static __mykapi void __init_frame_bitmap() {
	for(uint32_t i = 0; i < stats.frames.total; ++i) {
		frbitm[i] = 0;
	}

	uint32_t limit = stats.frames.total - stats.frames.allocator_used;
	for(uint32_t i = stats.frames.total - 1; i >= limit; --i) {
		frbitm[i] = ALLOCATOR_BUSY_FRAME;
	}
}

#define INIT_STATS() { \
	stats.phys.addrspc.start = low_phys_addr; \
	stats.phys.addrspc.end = high_phys_addr; \
	stats.phys.mem.total = total_mem; \
	stats.phys.mem.used = pages_to_bitmap << 12; \
	stats.phys.mem.free = total_mem - stats.phys.mem.used; \
	stats.phys.addrspc.end_until_alloc = stats.phys.addrspc.end - stats.phys.mem.used; \
	stats.frames.total = total_frames; \
	stats.frames.used = stats.frames.allocator_used = pages_to_bitmap; \
	stats.frames.free = stats.frames.total - stats.frames.used; \
	stats.frames.total_until_alloc = stats.frames.total - stats.frames.allocator_used; \
	stats.allocator_calls.allocs = 0; \
	stats.allocator_calls.frees = 0; \
}

__mykapi uint32_t mm_fralloc_init() {
	uint32_t low_phys_addr = __mm_memmap_get_avail_phys_mem_min();
	uint32_t high_phys_addr = __mm_memmap_get_avail_phys_mem_max();

	if((low_phys_addr & 0xfff) != 0) {
		return FRALLOC_INIT_LOW_ALIGNMENT;
	}

	if((high_phys_addr & 0xfff) != 0xfff) {
		return FRALLOC_INIT_HIGH_LAST_BYTE;
	}

	if(low_phys_addr >= high_phys_addr) {
		return FRALLOC_INIT_ILLEGAL_ARGS;
	}

	uint32_t high_phys_addr_aligned = 1 + high_phys_addr;
	uint32_t total_mem = high_phys_addr_aligned - low_phys_addr;
	uint32_t total_frames = total_mem >> 12;
	uint32_t pages_to_bitmap = 1 + (total_frames >> 12);

	if((pages_to_bitmap >> 10) >= 1) {
		return FRALLOC_INIT_TOO_MUCH_PAGES;
	}

	if(total_mem <= total_frames) {
		return FRALLOC_INIT_NOT_ENOUGH_MEMORY;
	}

	frbitm = __init_bitmap_pagetable(pages_to_bitmap, high_phys_addr_aligned);
	INIT_STATS();
	__init_frame_bitmap();

	return FRALLOC_INIT_OK;
}

#undef INIT_STATS

__mykapi uint32_t mm_fralloc_reserve() {
	++stats.allocator_calls.allocs;
	
	for(uint32_t i = 0; i < stats.frames.total_until_alloc; ++i) {
		if(frbitm[i] == 0) {
			stats.phys.mem.used += 4096;
			stats.phys.mem.free -= 4096;
			++stats.frames.used;
			--stats.frames.free;
			frbitm[i] = REGULAR_BUSY_FRAME;
			return stats.phys.addrspc.start + (i << 12);
		}
	}

	return FRALLOC_RESERVE_EXHAUSTED_MEMORY;
}

__mykapi uint32_t mm_fralloc_release(uint32_t phys) {
	++stats.allocator_calls.frees;
	
	if(unlikely(phys < stats.phys.addrspc.start || phys > stats.phys.addrspc.end_until_alloc)) {
		return FRALLOC_RELEASE_INVALID_PHYS;
	}

	uint32_t i = (phys - stats.phys.addrspc.start) >> 12;
	if(likely(frbitm[i] != 0)) {
		stats.phys.mem.used -= 4096;
		stats.phys.mem.free += 4096;
		--stats.frames.used;
		++stats.frames.free;
		frbitm[i] = 0;
		return FRALLOC_RELEASE_OK;
	}

	return FRALLOC_RELEASE_ALREADY_UNUSED;
}

__mykapi void mm_fralloc_log_init_err(uint32_t err) {
	const int8_t* strerr = "success";
	
	if(err == FRALLOC_INIT_LOW_ALIGNMENT) {
		strerr = "lower address must be aligned to 4096 int8_t boudary";
	} else if(err == FRALLOC_INIT_HIGH_LAST_BYTE) {
		strerr = "higher address must specify last int8_t 0x...fff";
	} else if(err == FRALLOC_INIT_ILLEGAL_ARGS) {
		strerr = "lower address is greater than higher address";
	} else if(err == FRALLOC_INIT_TOO_MUCH_PAGES) {
		strerr = "unusually big bitmap requires too much pages... kernel bug?";
	} else if(err == FRALLOC_INIT_NOT_ENOUGH_MEMORY) {
		strerr = "not enough memory to store frame bitmap";
	}

	kprintf("fralloc_init: %s\n", strerr);
}

__mykapi void mm_fralloc_log_reserve_err(uint32_t err) {
	const int8_t* strerr = "success";

	if(!FRALLOC_RESERVE_IS_OK(err)) {
		if(err == FRALLOC_RESERVE_EXHAUSTED_MEMORY) {
			strerr = "memory exhausted";
		}
	}

	kprintf("fralloc_reserve: %s\n", strerr);
}

__mykapi void mm_fralloc_log_release_err(uint32_t err) {
	const int8_t* strerr = "success";

	if(err == FRALLOC_RELEASE_ALREADY_UNUSED) {
		strerr = "already unused";
	} else if(err == FRALLOC_RELEASE_INVALID_PHYS) {
		strerr = "invalid physical address";
	}

	kprintf("fralloc_release: %s\n", strerr);
}

__mykapi mm_fralloc_stats mm_fralloc_get_stats() {
	return stats;
}

__mykapi void mm_fralloc_log_stats(const mm_fralloc_stats* s) {
	kprintf("fralloc_stats: physical address space starts @ %p\n"
			"fralloc_stats: physical address space ends @ %p\n"
			"fralloc_stats: usable physical address space ends @ %p\n"
			"fralloc_stats: %u bytes of memory are available\n"
			"fralloc_stats: used %u bytes of memory\n"
			"fralloc_stats: %u bytes of memory are free\n"
			"fralloc_stats: %u frames are managed by fralloc\n"
			"fralloc_stats: %u frames are currently in use\n"
			"fralloc_stats: %u frames (of %u in use) are reserved for fralloc usage\n"
			"fralloc_stats: %u frames are free\n"
			"fralloc_stats: %u allocation requests were made\n"
			"fralloc_stats: %u freeing requests were made\n", 
			s->phys.addrspc.start, s->phys.addrspc.end, s->phys.addrspc.end_until_alloc,
			s->phys.mem.total, s->phys.mem.used, s->phys.mem.free,
			s->frames.total, s->frames.used, s->frames.allocator_used, s->frames.used, s->frames.free,
			s->allocator_calls.allocs, s->allocator_calls.frees);
}
 
__mykapi uint32_t __mm_fralloc_get_bitmap_va() {
	return (uint32_t)frbitm;
}
