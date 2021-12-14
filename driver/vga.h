#ifndef VGA_MYKERNEL_H
#define VGA_MYKERNEL_H

#include <misc/types.h>
#include <misc/gcc.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

__mykapi mykt_int_16 vga_text_getc(mykt_uint_32 x, mykt_uint_32 y);
__mykapi void vga_text_putc(mykt_int_8 ch, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_32 x, mykt_uint_32 y);
__mykapi void vga_cursor_enable(mykt_uint_8 cursor_start, mykt_uint_8 cursor_end);
__mykapi void vga_cursor_disable();
__mykapi void vga_cursor_set_pos(mykt_uint_16 x, mykt_uint_16 y);
__mykapi mykt_pair_uint_16 vga_cursor_get_pos();

#endif
