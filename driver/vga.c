#include <x86/x86.h>
#include <driver/vga.h>

#define framebuf(x, y) *((word*)(0xffcb8000 + ((y * VGA_WIDTH + x) << 1)))

__mykapi word vga_text_getc(udword x, udword y) {
	return framebuf(x,y);
}

__mykapi void vga_text_putc(byte ch, byte bg, byte fg, udword x, udword y) {
	framebuf(x,y) = (word) (((bg << 4) | (fg & 0x0f) << 8) | ch);
}

__mykapi void vga_cursor_enable(ubyte cursor_start, ubyte cursor_end) {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, (byte) ((x86_inb(0x3d5) & 0xc0) | cursor_start));

	x86_outb(0x3d4, 0x0b);
	x86_outb(0x3d5, (byte) ((x86_inb(0x3d5) & 0xe0) | cursor_end));
}

__mykapi void vga_cursor_disable() {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, 0x20);
}

__mykapi void vga_cursor_set_pos(uword x, uword y) {
	uword pos = (uword) (y * VGA_WIDTH + x);

	x86_outb(0x3d4, 0x0f);
	x86_outb(0x3d5, (byte) (pos & 0xff));
	x86_outb(0x3d4, 0x0e);
	x86_outb(0x3d5, (byte) ((pos >> 8) & 0xff));
}

__mykapi pair_uword vga_cursor_get_pos() {
	uword pos = 0;

	x86_outb(0x3d4, 0x0f);
	pos |= (uword) x86_inb(0x3d5);

	x86_outb(0x3d4, 0x0e);
	pos |= (uword) (x86_inb(0x3d5) << 8);

	pair_uword coord;
	coord.x = pos % VGA_WIDTH;
	coord.y = pos / VGA_WIDTH;

	return coord;
}


