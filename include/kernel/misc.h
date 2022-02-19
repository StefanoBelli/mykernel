#ifndef MYKERNEL_MISC_H
#define MYKERNEL_MISC_H

#include <misc/gcc.h>

__mykapi void system_halt();
__mykapi void ksleep(uint32_t);
__mykapi void ksleep_init();


#endif
