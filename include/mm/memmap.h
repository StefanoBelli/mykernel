#ifndef MYKERNEL_MEMMAP_H
#define MYKERNEL_MEMMAP_H

#include <misc/gcc.h>
#include "types.h"

__mykapi uint32_t mm_memmap_seek();
__mykapi uint32_t mm_memmap_ptstore_setup();
__mykapi void mm_memmap_log_avail_memory();

#endif //MYKERNEL_MEMMAP_H
