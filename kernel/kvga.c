#include "kvga.h"
#include <driver/vga.h>

static mykt_uint_32 ix;
static mykt_uint_32 jy;

__mykapi void kvga_set_start_pos() {
	mykt_pair_uint_32 start_pos = vga_cursor_get_pos();
	ix = start_pos.x;
	jy = start_pos.y;
}

__mykapi void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_32 len, 
		void(*max_height_handle_policy)(mykt_int_8, mykt_int_8)) {

	for(mykt_uint_32 i = 0; i < len; ++i) {
		if(ix >= VGA_WIDTH) {
			ix = 0;
			++jy;
		}

		if(jy >= VGA_HEIGHT) {
			max_height_handle_policy(bg, fg);
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

__mykapi void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}

__mykapi void kvga_update_cursor() {
	vga_cursor_set_pos(ix, jy);
}

__mykapi void kvga_clear(mykt_int_8 bg, mykt_int_8 fg) {
	for(mykt_uint_32 k = 0; k < VGA_WIDTH; ++k) {
		for(mykt_uint_32 t = 0; t < VGA_HEIGHT; ++t) {
			vga_text_putc(' ', bg, fg, k, t);
		}
	}

	ix = 0;
	jy = 0;
}

__mykapi void kvga_scroll(mykt_int_8 bg, mykt_int_8 fg) {
	for(mykt_uint_32 k = 0; k < VGA_WIDTH; ++k) {
		for(mykt_uint_32 t = 1; t < VGA_HEIGHT; ++t) {
			mykt_int_8 ch = vga_text_getc(k, t) & 0xff;
			vga_text_putc(ch, bg, fg, k, t - 1);
		}
	}
	
	for (mykt_uint_32 k = 0; k < VGA_WIDTH; ++k) {
		vga_text_putc(' ', bg, fg, k, VGA_HEIGHT - 1);
	}

	ix = 0;
	jy = VGA_HEIGHT - 1;
}
