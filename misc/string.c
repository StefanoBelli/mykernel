#include "itoa.h"
#include "string.h"

__mykapi mykt_int_32 myk_strncpy(mykt_int_8* src, mykt_int_8* dst, mykt_int_32 dstlen) {
	const mykt_int_8* startsrc = src;
	mykt_int_32 wrote;
	while(((wrote = src - startsrc) < dstlen && (*dst++ = *src++))){}
	return wrote;
}

#define nextarg(type) \
	((type) *((int*) &fmt + argoff))

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
 * 
 * null-termination?
 */
mykt_int_32 myk_snprintf(mykt_int_8* buf, mykt_int_32 bufsiz, const mykt_int_8* fmt, ...) {
	const mykt_int_8* startbuf = buf;
	mykt_int_32 wrote = 0;
	mykt_int_32 argoff = 1;
	char auxbuf[33]; //needed for nextarg_* macro expansion

	while((wrote = buf - startbuf) < bufsiz && *fmt) {
		if(*fmt == '%') {
			mykt_int_32 maxlen = bufsiz - wrote;
			mykt_int_8 ch = *++fmt;

			if(ch == '%') {
				*buf++ = '%';
			} else if(ch == 'c') {
				*buf++ = nextarg_c();
			} else if(ch == 's') {
				buf += myk_strncpy(nextarg_s(), buf, maxlen);
			} else if(ch == 'p') {
				buf += myk_strncpy("0x", buf, maxlen);
				buf += myk_strncpy(nextarg_ul_hex(), buf, maxlen);
			} else if(ch == 'x') {
				buf += myk_strncpy(nextarg_ul_hex(), buf, maxlen);
			} else if(ch == 'b') {
				buf += myk_strncpy(nextarg_ul_bin(), buf, maxlen);
			} else if(ch == 'a') {
				buf += myk_strncpy(nextarg_us_hex(), buf, maxlen);
			} else if(ch == 'r') {
				buf += myk_strncpy(nextarg_us_bin(), buf, maxlen);
			} else if(ch == 'o') {
				buf += myk_strncpy(nextarg_ub_hex(), buf, maxlen);
			} else if(ch == 'g') {
				buf += myk_strncpy(nextarg_ub_bin(), buf, maxlen);
			} else if(ch == 'd') {
				buf += myk_strncpy(nextarg_si_dec(), buf, maxlen);
			} else if(ch == 'u') {
				buf += myk_strncpy(nextarg_ui_dec(), buf, maxlen);
			} else {
				buf += myk_strncpy("(invalid)", buf, maxlen);
			}
			
			++argoff;
		} else {
			*buf++ = *fmt++;
		}
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
