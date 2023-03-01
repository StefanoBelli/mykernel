#ifndef MM_KEBRK_H
#define MM_KEBRK_H

#include <misc/gcc.h>
#include "types.h"

#define KEBRK_FRALLOC_FAILURE ((void*)-1)
#define KEBRK_EXHAUSTED_MEMORY ((void*)0)

typedef struct {
	uint32_t good_calls;
	uint32_t total_calls;
	uint32_t lower_va;
	uint32_t higher_va;
} mm_kebrk_stats;

__mykapi void mm_kebrk_init();

__mykapi void* mm_kebrk();
__mykapi void mm_kebrk_log_err(void*);
__mykapi mm_kebrk_stats mm_kebrk_get_stats();
__mykapi void mm_kebrk_log_stats(const mm_kebrk_stats*);

#endif
