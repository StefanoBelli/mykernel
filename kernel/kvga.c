#include "kvga.h"
#include <driver/vga.h>

static mykt_uint_32 ix;
static mykt_uint_32 jy;

void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_64 len) {
	for(mykt_uint_64 i = 0; i < len; ++i) {
		if(ix >= VGA_WIDTH) {
			ix = 0;
			++jy;
		}

		if(jy >= VGA_HEIGHT) {
			kvga_clear(bg, fg);
		}

		if(data[i] == '\n') {
			ix = 0;
			++jy;
		} else if(data[i] == '\t') {
			ix += 4;
		} else if(data[i] == '\r') {
			ix = 0;
		} else {
			vga_text_putc(data[i], bg, fg, ix, jy);
			++ix;
		}
	}
}

void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}

void kvga_update_cursor() {
	vga_cursor_set_pos(ix, jy);
}

void kvga_clear(mykt_int_8 bg, mykt_int_8 fg) {
	for(mykt_uint_64 k = 0; k < VGA_WIDTH; ++k) {
		for(mykt_uint_64 t = 0; t < VGA_HEIGHT; ++t) {
			vga_text_putc(' ', bg, fg, k, t);
		}
	}

	ix = 0;
	jy = 0;
}
