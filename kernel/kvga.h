#ifndef KVGA_MYKERNEL_H
#define KVGA_MYKERNEL_H

#include <misc/types.h>
#include <misc/gcc.h>

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
} mykt_kvga_text_color;

__mykapi void kvga_set_start_pos();
__mykapi void kvga_write(
		const byte* data, byte bg, byte fg, udword len,
		__mykapi void(*max_height_handle_policy)(byte, byte));
__mykapi void kvga_cursor(ubyte cur_start, ubyte cur_end);
__mykapi void kvga_update_cursor();
__mykapi void kvga_clear(byte bg, byte fg);
__mykapi void kvga_scroll(byte bg, byte fg);

#endif
