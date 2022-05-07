#ifndef MM_KEBRK_H
#define MM_KEBRK_H

#include "types.h"

/*
 * kebrk - extend kernel break by size bytes
 * returns 
 *  * NULL if unable to extend program break more
 *  * addr pointer to extended area of size bytes
 */
void* kebrk(uint32_t size);

#endif
