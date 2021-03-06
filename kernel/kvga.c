#include <kernel/kvga.h>
#include <driver/vga.h>

static uint16_t ix;
static uint16_t jy;

__mykapi void kvga_set_start_pos() {
	pair_uword start_pos = vga_cursor_get_pos();
	ix = 0;
	jy = start_pos.y + 1;
}

__mykapi void kvga_write(const int8_t* data, int8_t bg, int8_t fg, uint32_t len,
                         __mykapi void(*max_height_handle_policy)(int8_t, int8_t)) {

	for(uint32_t i = 0; i < len; ++i) {
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

__mykapi void kvga_cursor(uint8_t cur_start, uint8_t cur_end) {
	if(cur_start == 0 && cur_end == 0) {
		vga_cursor_disable();
	} else {
		vga_cursor_enable(cur_start, cur_end);
	}
}

__mykapi void kvga_update_cursor() {
	vga_cursor_set_pos(ix, jy);
}

__mykapi void kvga_clear(int8_t bg, int8_t fg) {
	for(uint32_t k = 0; k < VGA_WIDTH; ++k) {
		for(uint32_t t = 0; t < VGA_HEIGHT; ++t) {
			vga_text_putc(' ', bg, fg, k, t);
		}
	}

	ix = 0;
	jy = 0;
}

__mykapi void kvga_scroll(int8_t bg, int8_t fg) {
	for(uint32_t k = 0; k < VGA_WIDTH; ++k) {
		for(uint32_t t = 1; t < VGA_HEIGHT; ++t) {
			int8_t ch = (int8_t) (vga_text_getc(k, t) & 0xff);
			vga_text_putc(ch, bg, fg, k, t - 1);
		}
	}
	
	for (uint32_t k = 0; k < VGA_WIDTH; ++k) {
		vga_text_putc(' ', bg, fg, k, VGA_HEIGHT - 1);
	}

	ix = 0;
	jy = VGA_HEIGHT - 1;
}
