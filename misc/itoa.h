#ifndef STRING_MYKERNEL_H
#define STRING_MYKERNEL_H

#include "types.h"
#include "gcc.h"

__mykapi mykt_int_8* ltoa(mykt_int_32 value, mykt_int_8* buf);
__mykapi mykt_int_8* ultoa(mykt_uint_32 value, mykt_int_8* buf, mykt_int_32 base);
__mykapi mykt_int_8* ustoa(mykt_uint_16 value, mykt_int_8* buf, mykt_int_32 base);
__mykapi mykt_int_8* ubtoa(mykt_uint_8 value, mykt_int_8* buf, mykt_int_32 base);

#endif
