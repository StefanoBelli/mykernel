#include <x86/x86.h>

void kmain() {
	x86_cli();
	x86_hlt();
}
