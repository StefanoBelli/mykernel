#include <x86/x86.h>
#include "vga.h"

void vga_text_putc(mykt_int_8 ch, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_32 x, mykt_uint_32 y) {
	mykt_int_16 fbch = ((bg << 4) | (fg & 0x0f) << 8) | ch;
	*((mykt_int_16*)(0xb8000 + ((y * VGA_WIDTH + x) << 1))) = fbch;
}

void vga_cursor_enable(mykt_uint_8 cursor_start, mykt_uint_8 cursor_end) {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, (x86_inb(0x3d5) & 0xc0) | cursor_start);

	x86_outb(0x3d4, 0x0b);
	x86_outb(0x3d5, (x86_inb(0x3d5) & 0xe0) | cursor_end);
}

void vga_cursor_disable() {
	x86_outb(0x3d4, 0x0a);
	x86_outb(0x3d5, 0x20);
}

void vga_cursor_set_pos(mykt_uint_32 x, mykt_uint_32 y) {
	mykt_uint_16 pos = y * VGA_WIDTH + x;

	x86_outb(0x3d4, 0x0f);
	x86_outb(0x3d5, (mykt_uint_8) (pos & 0xff));
	x86_outb(0x3d4, 0x0e);
	x86_outb(0x3d5, (mykt_uint_8) ((pos >> 8) & 0xff));
}

mykt_pair_uint_32 vga_cursor_get_pos() {
    mykt_uint_16 pos = 0;

    x86_outb(0x3d4, 0x0f);
    pos |= x86_inb(0x3d5);

    x86_outb(0x3d4, 0x0e);
    pos |= ((mykt_uint_16) x86_inb(0x3d5)) << 8;
    
    mykt_pair_uint_32 coord;
    coord.x = pos % VGA_WIDTH;
    coord.y = pos / VGA_WIDTH;

    return coord;
}


