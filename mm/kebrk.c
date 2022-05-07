#include <mm/fralloc.h>
#include <mm/kebrk.h>

#define KERNEL_INITIAL_BREAK_VA 0xc0400000

static uint32_t current_break = KERNEL_INITIAL_BREAK_VA; //incl
static uint32_t limit_break = 0; //excl

__mykapi void kebrk_init() {
	limit_break = __mm_fralloc_get_bitmap_va();
}

__mykapi void* kebrk(uint32_t size) {
	return (void*) 0;
}
