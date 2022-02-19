#ifndef KVGA_MYKERNEL_H
#define KVGA_MYKERNEL_H

#include "types.h"
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
        const int8_t* data, int8_t bg, int8_t fg, uint32_t len,
        __mykapi void(*max_height_handle_policy)(int8_t, int8_t));
__mykapi void kvga_cursor(uint8_t cur_start, uint8_t cur_end);
__mykapi void kvga_update_cursor();
__mykapi void kvga_clear(int8_t bg, int8_t fg);
__mykapi void kvga_scroll(int8_t bg, int8_t fg);

#endif
