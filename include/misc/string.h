#ifndef MYKERNEL_STRING_H
#define MYKERNEL_STRING_H

#include "types.h"
#include "gcc.h"

__mykapi udword myk_strncpy(const byte* src, byte* dst, udword dstlen);
__mykapi udword myk_vsnprintf(byte* buf, udword bufsiz, const byte* fmt, void* args);
__mykapi byte* myk_str_tok(byte* buf, byte tok);
__mykapi void* myk_memset(void* b, dword c, udword n);

#endif
