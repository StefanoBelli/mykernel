.extern kmain
.globl head
.text

page_tables_directory:
	.int 0x101000 | 3
	.fill 767, 4, 2
	.int 0x102000 | 3
	.int 0x101000 | 3
	.fill 254, 4, 2
bootstrap_page_table:
	.set i, 0
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr
kernel_page_table:
	.set i, 256
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr

head:
	movl $0x100000, %eax
	movl %eax, %cr3
	movl %cr0, %eax
	orl $0x80000000, %eax
	movl %eax, %cr0
	movl $0xc03fffff, %esp
	jmp kmain
