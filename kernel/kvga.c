#include "kvga.h"
#include <driver/vga.h>

void kvga_write(const mykt_int_8* data, mykt_int_8 bg, mykt_int_8 fg, mykt_uint_64 len) {

}

void kvga_cursor(mykt_uint_8 cur_start, mykt_uint_8 cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}
