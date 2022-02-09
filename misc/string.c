#include <misc/itoa.h>
#include <misc/string.h>

__mykapi udword myk_strncpy(const byte* src, byte* dst, udword dstlen) {
	const byte* startsrc = src;
	udword wrote;
	while(((wrote = (udword) (src - startsrc)) < dstlen && (*dst++ = *src++))){}
	return wrote;
}

#define nextarg(type) ((type) *((dword*) args + argoff))
#define nextarg_s() nextarg(byte*)
#define nextarg_c() nextarg(byte)
#define nextarg_ul_hex() ultoa(nextarg(udword), auxbuf, 16)
#define nextarg_ul_bin() ultoa(nextarg(udword), auxbuf, 2)
#define nextarg_us_hex() ustoa(nextarg(uword), auxbuf, 16)
#define nextarg_us_bin() ustoa(nextarg(uword), auxbuf, 2)
#define nextarg_ub_hex() ubtoa(nextarg(ubyte), auxbuf, 16)
#define nextarg_ub_bin() ubtoa(nextarg(ubyte), auxbuf, 2)
#define nextarg_ui_dec() ultoa(nextarg(udword), auxbuf, 10)
#define nextarg_si_dec() ltoa(nextarg(dword), auxbuf)
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
__mykapi udword myk_vsnprintf(byte* buf, udword bufsiz, const byte* fmt, void* args) {
	const byte* startbuf = buf;
	udword wrote = 0;
	dword argoff = 0;
	char auxbuf[33]; //needed for nextarg_* macro expansion

	while((wrote = (udword) (buf - startbuf)) < bufsiz && *fmt) {
		if(*fmt == '%') {
			udword maxlen = bufsiz - wrote;
			byte fmtch = *++fmt;

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

__mykapi byte* myk_str_tok(byte* buf, byte tok) {
	for(byte ch; (ch = *buf++);) {
		if(ch == tok) {
			return buf;
		}
	}

	return (byte*) 0;
}

__mykapi void* myk_memset(void* b, dword c, udword n) {
	ubyte* x = (ubyte*) b;
	for(; n > 0; --n) {
		*x++ = (ubyte) c;
	}

	return b;
}
