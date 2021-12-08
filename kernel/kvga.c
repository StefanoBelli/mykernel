#include "kvga.h"
#include <driver/vga.h>

void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_64 len) {
	mykt_pair_uint_32 start_pos = vga_cursor_get_pos();
	mykt_uint_32 ix = start_pos.x;
	mykt_uint_32 jy = start_pos.y;
	mykt_uint_64 wrote = 0;
	
	for(
			;
			wrote < len; 
			++ix, ++wrote
	) {
		vga_text_putc(data[wrote], bg, fg, ix, jy);

		if(ix == VGA_WIDTH) {
			ix = 0;
			++jy;
		}
	}

	vga_cursor_set_pos(ix, jy);
}

void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}
