#include <x86/x86.h>
#include <driver/vga.h>

#define framebuf(x, y) *((int16_t*)(0xffcb8000 + ((y * VGA_WIDTH + x) << 1)))

__mykapi int16_t vga_text_getc(uint32_t x, uint32_t y) {
	return framebuf(x,y);
}

__mykapi void vga_text_putc(int8_t ch, int8_t bg, int8_t fg, uint32_t x, uint32_t y) {
	framebuf(x,y) = (int16_t) (((bg << 4) | (fg & 0x0f) << 8) | ch);
}

__mykapi void vga_cursor_enable(uint8_t cursor_start, uint8_t cursor_end) {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, (int8_t) ((x86_inb(0x3d5) & 0xc0) | cursor_start));

	x86_outb(0x3d4, 0x0b);
	x86_outb(0x3d5, (int8_t) ((x86_inb(0x3d5) & 0xe0) | cursor_end));
}

__mykapi void vga_cursor_disable() {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, 0x20);
}

__mykapi void vga_cursor_set_pos(uint16_t x, uint16_t y) {
	uint16_t pos = (uint16_t) (y * VGA_WIDTH + x);

	x86_outb(0x3d4, 0x0f);
	x86_outb(0x3d5, (int8_t) (pos & 0xff));
	x86_outb(0x3d4, 0x0e);
	x86_outb(0x3d5, (int8_t) ((pos >> 8) & 0xff));
}

__mykapi pair_uword vga_cursor_get_pos() {
	uint16_t pos = 0;

	x86_outb(0x3d4, 0x0f);
	pos |= (uint16_t) x86_inb(0x3d5);

	x86_outb(0x3d4, 0x0e);
	pos |= (uint16_t) (x86_inb(0x3d5) << 8);

	pair_uword coord;
	coord.x = pos % VGA_WIDTH;
	coord.y = pos / VGA_WIDTH;

	return coord;
}


