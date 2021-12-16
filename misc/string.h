#ifndef MYKERNEL_STRING_H
#define MYKERNEL_STRING_H

#include "types.h"
#include "gcc.h"

#define myk_memset(b, c, n) { \
	mykt_uint_8* x = (mykt_uint_8*) b; \
	for(mykt_uint_32 i = 0; i < n; ++i) { \
		*x = (mykt_uint_8) c; \
	} \
}

__mykapi mykt_uint_32 myk_strncpy(const mykt_int_8* src, mykt_int_8* dst, mykt_uint_32 dstlen);
__mykapi mykt_uint_32 myk_vsnprintf(mykt_int_8* buf, mykt_uint_32 bufsiz, const mykt_int_8* fmt, void* args);
__mykapi mykt_int_8* myk_str_tok(mykt_int_8* buf, mykt_int_8 tok);

#endif
