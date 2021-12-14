#include "itoa.h"
#include "string.h"

__mykapi mykt_uint_32 myk_strncpy(const mykt_int_8* src, mykt_int_8* dst, mykt_uint_32 dstlen) {
	const mykt_int_8* startsrc = src;
	mykt_uint_32 wrote;
	while(((wrote = (mykt_uint_32) (src - startsrc)) < dstlen && (*dst++ = *src++))){}
	return wrote;
}

#define nextarg(type) ((type) *((mykt_int_32*) args + argoff))
#define nextarg_s() nextarg(mykt_int_8*)
#define nextarg_c() nextarg(mykt_int_8)
#define nextarg_ul_hex() ultoa(nextarg(mykt_uint_32), auxbuf, 16)
#define nextarg_ul_bin() ultoa(nextarg(mykt_uint_32), auxbuf, 2)
#define nextarg_us_hex() ustoa(nextarg(mykt_uint_16), auxbuf, 16)
#define nextarg_us_bin() ustoa(nextarg(mykt_uint_16), auxbuf, 2)
#define nextarg_ub_hex() ubtoa(nextarg(mykt_uint_8), auxbuf, 16)
#define nextarg_ub_bin() ubtoa(nextarg(mykt_uint_8), auxbuf, 2)
#define nextarg_ui_dec() ultoa(nextarg(mykt_uint_32), auxbuf, 10)
#define nextarg_si_dec() ltoa(nextarg(mykt_int_32), auxbuf)
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
__mykapi mykt_uint_32 myk_vsnprintf(mykt_int_8* buf, mykt_uint_32 bufsiz, const mykt_int_8* fmt, void* args) {
	const mykt_int_8* startbuf = buf;
	mykt_uint_32 wrote = 0;
	mykt_int_32 argoff = 0;
	char auxbuf[33]; //needed for nextarg_* macro expansion

	while((wrote = (mykt_uint_32) (buf - startbuf)) < bufsiz && *fmt) {
		if(*fmt == '%') {
			mykt_uint_32 maxlen = bufsiz - wrote;
			mykt_int_8 fmtch = *++fmt;

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

__mykapi mykt_int_8* myk_str_tok(mykt_int_8* buf, mykt_int_8 tok) {
	for(mykt_int_8 ch; (ch = *buf++);) {
		if(ch == tok) {
			return buf;
		}
	}

	return (mykt_int_8*) 0;
}

