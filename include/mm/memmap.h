#ifndef MYKERNEL_MEMMAP_H
#define MYKERNEL_MEMMAP_H

#include <misc/gcc.h>
#include "types.h"

__mykapi uint32_t mm_memmap_seek();
__mykapi uint32_t mm_memmap_ptstore_setup();

#endif //MYKERNEL_MEMMAP_H
