#ifndef MYKERNEL_KPRINTF_H
#define MYKERNEL_KPRINTF_H

#include <misc/gcc.h>
#include <misc/types.h>

#define KPRINTF_BUFSIZE 2048

typedef void(*__mykapi output_printer_fp)(const mykt_int_8*, mykt_uint_32);
typedef void(*__mykapi your_init_steps_fp)();

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
mykt_uint_32 kprintf(const mykt_int_8* fmt, ...);
__mykapi void kprintf_init(output_printer_fp print, your_init_steps_fp more_steps);
__mykapi void kprintf_flush();

#endif
