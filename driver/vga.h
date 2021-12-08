#ifndef VGA_MYKERNEL_H
#define VGA_MYKERNEL_H

#include <common/types.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_text_putc(mykt_int_8 ch, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_32 x, mykt_uint_32 y);
void vga_cursor_enable(mykt_uint_8 cursor_start, mykt_uint_8 cursor_end);
void vga_cursor_disable();
void vga_cursor_set_pos(mykt_uint_32 x, mykt_uint_32 y);
mykt_pair32 vga_cursor_get_pos();

#endif
