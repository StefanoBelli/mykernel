#ifndef VGA_MYKERNEL_H
#define VGA_MYKERNEL_H

#include <misc/types.h>
#include <misc/gcc.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

__mykapi word vga_text_getc(udword x, udword y);
__mykapi void vga_text_putc(byte ch, byte bg, byte fg, udword x, udword y);
__mykapi void vga_cursor_enable(ubyte cursor_start, ubyte cursor_end);
__mykapi void vga_cursor_disable();
__mykapi void vga_cursor_set_pos(uword x, uword y);
__mykapi pair_uword vga_cursor_get_pos();

#endif
