#ifndef MYKERNEL_KSLEEP_H
#define MYKERNEL_KSLEEP_H

#include <misc/gcc.h>
#include <misc/types.h>

__mykapi void ksleep(udword);
__mykapi void ksleep_init();

#endif
