#include <misc/string.h>
#include "kprintf.h"

typedef struct __buffer {
	byte data[KPRINTF_BUFSIZE];
	udword len;
	output_printer_fp print;
	void (*__mykapi flush)(struct __buffer*);
	void (*__mykapi write)(byte*, udword, struct __buffer*);
	void (*__mykapi append)(byte*, udword, struct __buffer*);
} buffer;

static buffer kprintf_buffer;

static __mykapi void __buffer_flush(buffer* buf) {
	if(buf->len > 0) {
		buf->print(buf->data, buf->len);
		buf->len = 0;
	}
}

static __mykapi void __buffer_append(byte* src, udword len, buffer* buf) {
	myk_strncpy(src, buf->data + buf->len, len);
	buf->len += len;
}

static __mykapi void __buffer_write(byte* src, udword len, buffer* buf) {
	if(unlikely(buf->len + len > KPRINTF_BUFSIZE)) {
		buf->flush(buf);
	}

	byte* last = src;
	const byte* origin = src;

	if(likely((src = myk_str_tok(src, '\n')) != (byte*)0)) {
		buf->flush(buf);

		do {
			buf->print(last, (udword) (src - last));
			last = src;
		} while((src = myk_str_tok(src, '\n')));
	}

	udword applen = len - (udword) last + (udword) origin;
	buf->append(last, applen, buf);
}

/* exposed */
udword kprintf(const byte* fmt, ...) {
	byte local_buf[KPRINTF_BUFSIZE];
	udword wrote = myk_vsnprintf(local_buf, KPRINTF_BUFSIZE, fmt, &fmt + 1);
	kprintf_buffer.write(local_buf, wrote, &kprintf_buffer);

	return wrote;
}

__mykapi void kprintf_init(output_printer_fp print, your_init_steps_fp more_steps) {
	kprintf_buffer.len = 0;
	kprintf_buffer.print = print;
	kprintf_buffer.flush = __buffer_flush;
	kprintf_buffer.write = __buffer_write;
	kprintf_buffer.append = __buffer_append;
	
	more_steps();
}

__mykapi void kprintf_flush() {
	kprintf_buffer.flush(&kprintf_buffer);
}
