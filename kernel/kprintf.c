#include <misc/string.h>
#include <kernel/kprintf.h>

typedef struct __buffer {
	int8_t data[KPRINTF_BUFSIZE];
	uint32_t len;
	output_printer_fp print;
	void (*__mykapi flush)(struct __buffer*);
	void (*__mykapi write)(int8_t*, uint32_t, struct __buffer*);
	void (*__mykapi append)(int8_t*, uint32_t, struct __buffer*);
} buffer;

static buffer kprintf_buffer;

static __mykapi void __buffer_flush(buffer* buf) {
	if(buf->len > 0) {
		buf->print(buf->data, buf->len);
		buf->len = 0;
	}
}

static __mykapi void __buffer_append(int8_t* src, uint32_t len, buffer* buf) {
	myk_strncpy(src, buf->data + buf->len, len);
	buf->len += len;
}

static __mykapi void __buffer_write(int8_t* src, uint32_t len, buffer* buf) {
	if(unlikely(buf->len + len > KPRINTF_BUFSIZE)) {
		buf->flush(buf);
	}

	int8_t* last = src;
	const int8_t* origin = src;

	if(likely((src = myk_str_tok(src, '\n')) != (int8_t*)0)) {
		buf->flush(buf);

		do {
			buf->print(last, (uint32_t) (src - last));
			last = src;
		} while((src = myk_str_tok(src, '\n')));
	}

	uint32_t applen = len - (uint32_t) last + (uint32_t) origin;
	buf->append(last, applen, buf);
}

/* exposed */
uint32_t kprintf(const int8_t* fmt, ...) {
	int8_t local_buf[KPRINTF_BUFSIZE];
	uint32_t wrote = myk_vsnprintf(local_buf, KPRINTF_BUFSIZE, fmt, &fmt + 1);
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
