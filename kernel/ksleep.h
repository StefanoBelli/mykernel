#ifndef MYKERNEL_KSLEEP_H
#define MYKERNEL_KSLEEP_H

#include <misc/gcc.h>
#include <misc/types.h>

__mykapi void __ksleep_tick();
__mykapi void ksleep(mykt_int_32);

#endif
