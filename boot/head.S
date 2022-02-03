.extern kmain
.globl head
.text

# 0x100000
kernel_page_tables:
	.set i, 0
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr

# 0x101000
page_directory:
	.int 0x100000 | 3
	.fill 1023, 4, 2

head:
	movl $0x101000, %eax
	movl %eax, %cr3
	movl %cr0, %eax
	orl $0x80000000, %eax
	movl %eax, %cr0
	jmp kmain
