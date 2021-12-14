#ifndef MYKERNEL_STRING_H
#define MYKERNEL_STRING_H

#include "types.h"
#include "gcc.h"

__mykapi mykt_uint_32 myk_strncpy(const mykt_int_8* src, mykt_int_8* dst, mykt_uint_32 dstlen);
__mykapi mykt_uint_32 myk_vsnprintf(mykt_int_8* buf, mykt_uint_32 bufsiz, const mykt_int_8* fmt, void* args);
__mykapi mykt_int_8* myk_str_tok(mykt_int_8* buf, mykt_int_8 tok);

#endif
