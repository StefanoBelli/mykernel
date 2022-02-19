#include <misc/itoa.h>

__mykapi int8_t* ltoa(int32_t value, int8_t* buf) {
	int32_t numlen = 0;
	int32_t sign = 0;

	if(value < 0) {
		sign = 1;
		value = -value;
	}

	int32_t oldvalue = value;

	do {
		++numlen;
	} while ((value /= 10));

	buf[numlen + sign] = 0;

	int32_t i;
	for (i = numlen - 1 + sign; i >= sign; --i) {
		buf[i] = (int8_t) (oldvalue % 10) + 48;
		oldvalue /= 10;
	}

	if (i == 0) {
		buf[0] = '-';
	}

	return buf;
}

/* unsigned */
__mykapi int8_t* ultoa(uint32_t value, int8_t* buf, uint8_t base) {
	int32_t numlen = 0;
	uint32_t oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (int32_t i = numlen - 1; i >= 0; --i) {
		uint32_t rem = oldvalue % base;
		buf[i] = (int8_t) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi int8_t* ustoa(uint16_t value, int8_t* buf, uint8_t base) {
	int32_t numlen = 0;
	uint16_t oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (int32_t i = numlen - 1; i >= 0; --i) {
		uint32_t rem = oldvalue % base;
		buf[i] = (int8_t) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}

__mykapi int8_t* ubtoa(uint8_t value, int8_t* buf, uint8_t base) {
	int32_t numlen = 0;
	uint8_t oldvalue = value;

	do {
		++numlen;
	} while ((value /= base));

	buf[numlen] = 0;

	for (int32_t i = numlen - 1; i >= 0; --i) {
		uint32_t rem = oldvalue % base;
		buf[i] = (int8_t) (rem > 9 ? rem + 87 : rem + 48);
		oldvalue /= base;
	}

	return buf;
}
