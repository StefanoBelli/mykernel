#define KERNEL_INITIAL_BREAK_VASTART 0
#define RESERVED_VASTART 0

#include <mm/kebrk.h>

static const void* const brkman_area_start = KERNEL_INITIAL_BREAK_VASTART;
static const void* const brkman_area_end = RESERVED_VASTART;
 
void* kebrk(uint32_t size) {
	return (void*) 0;
}
