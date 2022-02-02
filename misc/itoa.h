#ifndef STRING_MYKERNEL_H
#define STRING_MYKERNEL_H

#include "types.h"
#include "gcc.h"

__mykapi byte* ltoa(dword value, byte* buf);
__mykapi byte* ultoa(udword value, byte* buf, ubyte base);
__mykapi byte* ustoa(uword value, byte* buf, ubyte base);
__mykapi byte* ubtoa(ubyte value, byte* buf, ubyte base);

#endif
