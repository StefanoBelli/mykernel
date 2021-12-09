#include "kvga.h"
#include <driver/vga.h>

static mykt_uint_32 ix;
static mykt_uint_32 jy;

void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_64 len) {
	/*for(mykt_uint_64 wrote = 0; wrote < len;) {
		if(ix == VGA_WIDTH) {
			ix = 0;
			++jy;
		}

		if(jy == VGA_HEIGHT) {
			ix = 0;
			jy = 0;
		}

		vga_text_putc(data[wrote], bg, fg, ix, jy);
		++wrote;
		++ix;
		++wrote;
	}

	vga_cursor_set_pos(ix, jy); */
}

void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}
