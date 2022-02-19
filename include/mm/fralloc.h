#ifndef MMAN_FRAME_ALLOCATOR_H
#define MMAN_FRAME_ALLOCATOR_H

#include "types.h"
#include <misc/gcc.h>

#define FRALLOC_INIT_LOW_ALIGNMENT 1
#define FRALLOC_INIT_HIGH_LAST_BYTE 2
#define FRALLOC_INIT_ILLEGAL_ARGS 3
#define FRALLOC_INIT_TOO_MUCH_PAGES 4
#define FRALLOC_INIT_NOT_ENOUGH_MEMORY 5
#define FRALLOC_INIT_OK 0

typedef struct {
	struct {
		struct {
			uint32_t start;
			uint32_t end;
		} addrspc;

		struct {
			uint32_t total;
			uint32_t used;
			uint32_t free;
		} mem;
	} phys;

	struct {
		uint32_t total;
		uint32_t used;
		uint32_t allocator_used;
		uint32_t free;
	} frames;

	struct {
		uint32_t allocs;
		uint32_t frees;
	} allocator_calls;
} mm_fralloc_stats;

__mykapi mm_fralloc_stats mm_fralloc_get_stats();
__mykapi void mm_fralloc_log_stats(const mm_fralloc_stats*);
__mykapi void mm_fralloc_log_init_err(uint32_t);
__mykapi uint32_t mm_fralloc_init();
__mykapi uint32_t mm_fralloc_reserve();
__mykapi uint32_t mm_fralloc_release(uint32_t);

#endif
