.extern kmain
.globl head
.text

# 0x100000
bootstrap_idmap_page_table:
	.set i, 0
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr
# 0x101000
kernel_page_tables:
	.set i, 256
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr
# 0x102000
	.set i, 1281
	.rept 1024
	.int (i * 0x1000) | 3
	.set i, i + 1
	.endr
# 0x103000
page_tables_directory:
	.int 0x100000 | 3		# 0
	.fill 767, 4, 2			# 767
	.int 0x101000 | 3		# 768
	.int 0x102000 | 3		# 769
	.fill 254, 4, 2

head:
	movl $0x103000, %eax
	movl %eax, %cr3
	movl %cr0, %eax
	orl $0x80000000, %eax
	movl %eax, %cr0
	jmp kmain
