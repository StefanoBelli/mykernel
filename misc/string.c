#include <misc/itoa.h>
#include <misc/string.h>

__mykapi uint32_t myk_strncpy(const int8_t* src, int8_t* dst, uint32_t dstlen) {
	const int8_t* startsrc = src;
	uint32_t wrote;
	while(((wrote = (uint32_t) (src - startsrc)) < dstlen && (*dst++ = *src++))){}
	return wrote;
}

#define nextarg(type) ((type) *((int32_t*) args + argoff))
#define nextarg_s() nextarg(int8_t*)
#define nextarg_c() nextarg(int8_t)
#define nextarg_ul_hex() ultoa(nextarg(uint32_t), auxbuf, 16)
#define nextarg_ul_bin() ultoa(nextarg(uint32_t), auxbuf, 2)
#define nextarg_us_hex() ustoa(nextarg(uint16_t), auxbuf, 16)
#define nextarg_us_bin() ustoa(nextarg(uint16_t), auxbuf, 2)
#define nextarg_ub_hex() ubtoa(nextarg(uint8_t), auxbuf, 16)
#define nextarg_ub_bin() ubtoa(nextarg(uint8_t), auxbuf, 2)
#define nextarg_ui_dec() ultoa(nextarg(uint32_t), auxbuf, 10)
#define nextarg_si_dec() ltoa(nextarg(int32_t), auxbuf)
#define buf_app_s(s) (buf += myk_strncpy(s, buf, maxlen))
#define buf_app_c(c) (*buf++ = c)
	
/*
 * %%: %
 * %c: char
 * %s: NUL-terminated string
 * %p: 32-bit pointer (0xdeadcode)
 * %x: 32-bit unsigned hexadecimal integer (lowercase)
 * %b: 32-bit unsigned binary integer
 * %a: 16-bit unsigned hexadecimal integer (lowercase)
 * %r: 16-bit unsigned binary integer
 * %o: 8-bit unsigned hexadecimal integer (lowercase)
 * %g: 8-bit unsigned binary integer
 * %d: decimal integer
 * %u: unsigned decimal integer
 */
__mykapi uint32_t myk_vsnprintf(int8_t* buf, uint32_t bufsiz, const int8_t* fmt, void* args) {
	const int8_t* startbuf = buf;
	uint32_t wrote = 0;
	int32_t argoff = 0;
	char auxbuf[33]; //needed for nextarg_* macro expansion

	while((wrote = (uint32_t) (buf - startbuf)) < bufsiz && *fmt) {
		if(*fmt == '%') {
			uint32_t maxlen = bufsiz - wrote;
			int8_t fmtch = *++fmt;

			if(fmtch == '%') {
				buf_app_c('%');
			} else if(fmtch == 'c') {
				buf_app_c(nextarg_c());
			} else if(fmtch == 's') {
				buf_app_s(nextarg_s());
			} else if(fmtch == 'p') {
				buf_app_s("0x");
				buf_app_s(nextarg_ul_hex());
			} else if(fmtch == 'x') {
				buf_app_s(nextarg_ul_hex());
			} else if(fmtch == 'b') {
				buf_app_s(nextarg_ul_bin());
			} else if(fmtch == 'a') {
				buf_app_s(nextarg_us_hex());
			} else if(fmtch == 'r') {
				buf_app_s(nextarg_us_bin());
			} else if(fmtch == 'o') {
				buf_app_s(nextarg_ub_hex());
			} else if(fmtch == 'g') {
				buf_app_s(nextarg_ub_bin());
			} else if(fmtch == 'd') {
				buf_app_s(nextarg_si_dec());
			} else if(fmtch == 'u') {
				buf_app_s(nextarg_ui_dec());
			} else {
				buf_app_s("(invalidfmt)");
			}
			
			++argoff;
		} else {
			buf_app_c(*fmt);
		}

		++fmt;
	}
	
	if(wrote < bufsiz) {
		*buf = 0;
	}

	return wrote;
}

#undef nextarg
#undef nextarg_c
#undef nextarg_s
#undef nextarg_ul_hex
#undef nextarg_ul_bin
#undef nextarg_us_hex
#undef nextarg_us_bin
#undef nextarg_ub_hex
#undef nextarg_ub_bin
#undef nextarg_si_dec
#undef nextarg_ui_dec
#undef buf_app_s
#undef buf_app_c

__mykapi int8_t* myk_str_tok(int8_t* buf, int8_t tok) {
	for(int8_t ch; (ch = *buf++);) {
		if(ch == tok) {
			return buf;
		}
	}

	return (int8_t*) 0;
}

__mykapi void* myk_memset(void* b, int32_t c, uint32_t n) {
	uint8_t* x = (uint8_t*) b;
	for(; n > 0; --n) {
		*x++ = (uint8_t) c;
	}

	return b;
}
