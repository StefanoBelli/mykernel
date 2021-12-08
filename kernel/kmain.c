#include <x86/x86.h>
#include "kvga.h"

void kmain() {
	char c[80] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	kvga_write(c, VGA_TEXT_COLOR_BLACK, VGA_TEXT_COLOR_WHITE, 80);


	x86_cli();
	x86_hlt();
}
