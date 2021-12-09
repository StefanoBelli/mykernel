#ifndef KVGA_MYKERNEL_H
#define KVGA_MYKERNEL_H

#include <x86/types.h>

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


void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_64 len);
void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end);
void kvga_update_cursor();
void kvga_clear(mykt_int_8 bg, mykt_int_8 fg);

#endif
