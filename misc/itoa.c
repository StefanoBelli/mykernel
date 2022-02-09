#include <misc/itoa.h>

__mykapi byte* ltoa(dword value, byte* buf) {
	dword numlen = 0;
	dword sign = 0;

	if(value < 0) {
		sign = 1;
		value = -value;
	}

	dword oldvalue = value;

	do {
		++numlen;
	} while ((value /= 10));

	buf[numlen + sign] = 0;

	dword i;
	for (i = numlen - 1 + sign; i >= sign; --i) {
		buf[i] = (byte) (oldvalue % 10) + 48;
		oldvalue /= 10;
	}

	if (i == 0) {
		buf[0] = '-';
	}

	return buf;
}

/* unsigned */
__mykapi byte* ultoa(udword value, byte* buf, ubyte base) {
	dword numlen = 0;
	udword oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (dword i = numlen - 1; i >= 0; --i) {
		udword rem = oldvalue % base;
		buf[i] = (byte) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi byte* ustoa(uword value, byte* buf, ubyte base) {
	dword numlen = 0;
	uword oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (dword i = numlen - 1; i >= 0; --i) {
		udword rem = oldvalue % base;
		buf[i] = (byte) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi byte* ubtoa(ubyte value, byte* buf, ubyte base) {
	dword numlen = 0;
	ubyte oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (dword i = numlen - 1; i >= 0; --i) {
		udword rem = oldvalue % base;
		buf[i] = (byte) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}
