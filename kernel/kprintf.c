#include <misc/string.h>
#include "kvga.h"
#include "kprintf.h"

#define BUFSIZE 8192

typedef struct __buffer {
	mykt_int_8 data[BUFSIZE];
	mykt_int_32 len;
	void (*flush)(struct __buffer*);
	void (*write)(mykt_int_8*, mykt_int_32, struct __buffer*);
} buffer;

static __mykapi void __buffer_flush(buffer* buf) {
	if(buf->len > 0) {
		kvga_write(buf->data, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE, buf->len, kvga_scroll);
		buf->len = 0;
	}
}

static __mykapi void __buffer_write(mykt_int_8* src, mykt_int_32 len, buffer* buf) {

}

mykt_int_32 kprintf(const mykt_int_8* fmt, ...) {
	return 0;
}

void kprintf_init() {

}
