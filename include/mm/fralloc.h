#ifndef MMAN_FRAME_ALLOCATOR_H
#define MMAN_FRAME_ALLOCATOR_H

#include <misc/types.h>
#include <misc/gcc.h>

typedef struct {
	struct {
		struct {
			udword start;
			udword end;
		} addrspc;

		struct {
			udword total;
			udword used;
			udword free;
		} mem;
	} phys;

	struct {
		udword total;
		udword used;
		udword allocator_used;
		udword free;
	} frames;

	struct {
		udword allocs;
		udword frees;
	} allocator_calls;
} mm_fralloc_stats;

__mykapi mm_fralloc_stats mm_fralloc_get_stats();
__mykapi void mm_fralloc_log_stats(const mm_fralloc_stats*);
__mykapi udword mm_fralloc_init(udword, udword);
__mykapi udword mm_fralloc_reserve();
__mykapi udword mm_fralloc_release(udword);

#endif
