#ifndef MYKERNEL_KPRINTF_H
#define MYKERNEL_KPRINTF_H

#include <misc/types.h>

/*
 * %%: %
 * %c: char
 * %s: NUL-terminated string
 * %p: 32-bit pointer (0xdeadcode)
 * %x: 32-bit unsigned hexadecimal integer (lowercase)
 * %b: 32-bit unsigned binary integer
 * %a: 16-bit unsigned hexadecimal integer (lowercase)
 * %r: 16-bit unsigned binary integer
 * %o: 8-bit unsigned hexadecimal integer (lowercase)
 * %g: 8-bit unsigned binary integer
 * %d: decimal integer
 * %u: unsigned decimal integer
 */
mykt_int_32 kprintf(const mykt_int_8* fmt, ...);

#endif
