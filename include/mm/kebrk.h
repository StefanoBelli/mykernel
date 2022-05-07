#ifndef MM_KEBRK_H
#define MM_KEBRK_H

#include <misc/gcc.h>
#include "types.h"

__mykapi void kebrk_init();

/*
 * kebrk - extend kernel break by size bytes
 * returns 
 *  * NULL if unable to extend program break more
 *  * addr pointer to extended area of size bytes
 */
__mykapi void* kebrk(uint32_t size);

#endif
