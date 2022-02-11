.extern kmain
.globl head

.macro new_filled_pt start
	.set i, \start
	.rept 1024
		.int (i * 0x1000) | 3
		.set i, i + 1
	.endr
.endm

.text

page_tables_directory:
	.int 0x101000 | 3
	.fill 767, 4, 2
	.int 0x102000 | 3
	.fill 254, 4, 2
	.int 0x101000 | 3
bootstrap_page_table:
	new_filled_pt 0
kernel_page_table:
	new_filled_pt 0x100
	
va_gdt:
	.quad 0
	.word 0xffff
	.word 0
	.byte 0
	.byte 0b10011010
	.byte 0b11001111
	.byte 0
	.word 0xffff
	.word 0
	.byte 0
	.byte 0b10010010
	.byte 0b11001111
	.byte 0
va_gdt_desc:
	.word va_gdt_desc - va_gdt - 1
	.int 0xc0000000 + va_gdt - 0x100000

head:
	movl $page_tables_directory, %eax
	movl %eax, %cr3
	movl %cr0, %eax
	orl $0x80000000, %eax
	movl %eax, %cr0
	movl $0xc03fffff, %esp
	lgdtl 0xc0000000 + va_gdt_desc - 0x100000
	jmp kmain
