#include "itoa.h"

__mykapi mykt_int_8* ltoa(mykt_int_32 value, mykt_int_8* buf) {
	mykt_int_32 numlen = 0;
	mykt_int_32 sign = 0;

	if(value < 0) {
		sign = 1;
		value = -value;
	}

	mykt_int_32 oldvalue = value;

	do {
		++numlen;
	} while ((value /= 10));

	buf[numlen + sign] = 0;

	mykt_int_32 i;
	for (i = numlen - 1 + sign; i >= sign; --i) {
		buf[i] = (mykt_int_8) (oldvalue % 10) + 48;
		oldvalue /= 10;
	}

	if (i == 0) {
		buf[0] = '-';
	}

	return buf;
}

/* unsigned */
__mykapi mykt_int_8* ultoa(mykt_uint_32 value, mykt_int_8* buf, mykt_uint_8 base) {
	mykt_int_32 numlen = 0;
	mykt_uint_32 oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (mykt_int_32 i = numlen - 1; i >= 0; --i) {
		mykt_uint_32 rem = oldvalue % base;
		buf[i] = (mykt_int_8) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi mykt_int_8* ustoa(mykt_uint_16 value, mykt_int_8* buf, mykt_uint_8 base) {
	mykt_int_32 numlen = 0;
	mykt_uint_16 oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (mykt_int_32 i = numlen - 1; i >= 0; --i) {
		mykt_uint_32 rem = oldvalue % base;
		buf[i] = (mykt_int_8) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi mykt_int_8* ubtoa(mykt_uint_8 value, mykt_int_8* buf, mykt_uint_8 base) {
	mykt_int_32 numlen = 0;
	mykt_uint_8 oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (mykt_int_32 i = numlen - 1; i >= 0; --i) {
		mykt_uint_32 rem = oldvalue % base;
		buf[i] = (mykt_int_8) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}
