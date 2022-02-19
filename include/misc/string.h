#ifndef MYKERNEL_STRING_H
#define MYKERNEL_STRING_H

#include "types.h"
#include "gcc.h"

__mykapi uint32_t myk_strncpy(const int8_t* src, int8_t* dst, uint32_t dstlen);
__mykapi uint32_t myk_vsnprintf(int8_t* buf, uint32_t bufsiz, const int8_t* fmt, void* args);
__mykapi int8_t* myk_str_tok(int8_t* buf, int8_t tok);
__mykapi void* myk_memset(void* b, int32_t c, uint32_t n);

#endif
