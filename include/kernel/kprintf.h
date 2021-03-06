#ifndef MYKERNEL_KPRINTF_H
#define MYKERNEL_KPRINTF_H

#include <misc/gcc.h>
#include "types.h"

#define KPRINTF_BUFSIZE 8192

typedef void(*__mykapi output_printer_fp)(const int8_t*, uint32_t);
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
uint32_t kprintf(const int8_t* fmt, ...);
__mykapi void kprintf_init(output_printer_fp print, your_init_steps_fp more_steps);
__mykapi void kprintf_flush();

#endif
