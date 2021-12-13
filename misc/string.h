#ifndef MYKERNEL_STRING_H
#define MYKERNEL_STRING_H

#include "types.h"
#include "gcc.h"

__mykapi mykt_int_32 myk_strncpy(const mykt_int_8* src, mykt_int_8* dst, mykt_int_32 dstlen);
mykt_int_32 myk_snprintf(mykt_int_8* buf, mykt_int_32 bufsiz, const mykt_int_8* fmt, ...);
__mykapi mykt_int_8* myk_str_tok(mykt_int_8* buf, mykt_int_8 tok);

#endif
