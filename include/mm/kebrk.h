#ifndef MM_KEBRK_H
#define MM_KEBRK_H

#include <misc/gcc.h>
#include "types.h"

#define KEBRK_FRALLOC_FAILURE ((void*)-1)
#define KEBRK_EXHAUSTED_MEMORY ((void*)0)

__mykapi void kebrk_init();

/*
 * kebrk - extend kernel break by one page size
 * returns:
 *  - KEBRK_FRALLOC_FAILURE
 *  - KEBRK_EXHAUSTED_MEMORY
 *  - virtaddr
 */
__mykapi void* kebrk();

#endif
