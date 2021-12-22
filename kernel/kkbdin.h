#ifndef MYKERNEL_KKBDIN_H
#define MYKERNEL_KKBDIN_H

#include <misc/gcc.h>
#include <misc/types.h>

__mykapi mykt_int_32 kkbdin_init();
__mykapi mykt_int_32 kkbdin_read(mykt_int_8 *dest, mykt_int_32 size);

#endif
