int data = 0xdeadbeef;
int moredata = 0xdeadc0de;
int uninit_data;

/*
 * kernel code gets loaded @ 0x100000 [from 0x7e00]
 */
void kmain() {
	/*
	 * TODO -- HIGHEST PRIORITY
	 *  kernel data is getting loaded here @ 0x200000 [from 0x100200]
	 */
	__asm__("cli;hlt;");
}
