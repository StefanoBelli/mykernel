#ifndef VGA_MYKERNEL_H
#define VGA_MYKERNEL_H

#include <common/types.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
	VGA_TEXT_COLOR_BLACK,
	VGA_TEXT_COLOR_BLUE,
	VGA_TEXT_COLOR_GREEN,
	VGA_TEXT_COLOR_CYAN,
	VGA_TEXT_COLOR_RED,
	VGA_TEXT_COLOR_MAGENTA,
	VGA_TEXT_COLOR_BROWN,
	VGA_TEXT_COLOR_LIGHT_GREY,
	VGA_TEXT_COLOR_DARK_GRAY,
	VGA_TEXT_COLOR_LIGHT_BLUE,
	VGA_TEXT_COLOR_LIGHT_GREEN,
	VGA_TEXT_COLOR_LIGHT_CYAN,
	VGA_TEXT_COLOR_LIGHT_RED,
	VGA_TEXT_COLOR_LIGHT_MAGENTA,
	VGA_TEXT_COLOR_YELLOW,
	VGA_TEXT_COLOR_WHITE
} mykt_vga_text_color;

void vga_text_putc(mykt_int_8 ch, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_32 x, mykt_uint_32 y);
void vga_cursor_enable(mykt_uint_8 cursor_start, mykt_uint_8 cursor_end);
void vga_cursor_disable();
void vga_cursor_set_pos(mykt_uint_32 x, mykt_uint_32 y);
mykt_pair32 vga_cursor_get_pos();

#endif
