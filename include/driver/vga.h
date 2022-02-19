#ifndef VGA_MYKERNEL_H
#define VGA_MYKERNEL_H

#include "types.h"
#include <misc/gcc.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

__mykapi int16_t vga_text_getc(uint32_t x, uint32_t y);
__mykapi void vga_text_putc(int8_t ch, int8_t bg, int8_t fg, uint32_t x, uint32_t y);
__mykapi void vga_cursor_enable(uint8_t cursor_start, uint8_t cursor_end);
__mykapi void vga_cursor_disable();
__mykapi void vga_cursor_set_pos(uint16_t x, uint16_t y);
__mykapi pair_uword vga_cursor_get_pos();

#endif
