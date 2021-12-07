.globl _start
.extern kmain
.text
_start:
.code16
xorw %ax, %ax
movw %ax, %ds
movw %ax, %ss
movw $0x8000, %bp
movw %bp, %sp

movb $3, %al
int $16

pushw %dx

movw $s_boot_start, %si
call bios_printzln

popw %dx

cli

call test_a20
testb %al, %al
jnz load_kernel

movw $0x2401, %ax
int $0x15

call test_a20
testb %al, %al
jnz load_kernel

inb $0x92, %al
orb $2, %al
outb %al, $0x92

call test_a20
testb %al, %al
jnz load_kernel

inb $0xee, %al

call test_a20
testb %al, %al
jnz load_kernel

movw $s_a20_givenup, %si
call bios_printzln
jmp cpu_halt

load_kernel: #also load kernel data
movw $0x202, %ax
movw $2, %cx
xorb %dh, %dh
movw $0xffff, %bx
movw %bx, %es
movw $0x10, %bx
int $0x13
jnc prepare_pm

movw $s_read_boot_disk_failure, %si
call bios_printzln
jmp cpu_halt

prepare_pm:
lgdtl gdt_desc
movl %cr0, %eax
orb $1, %al
movl %eax, %cr0

ljmpl $8, $enter_pm

.code32
enter_pm:
movw $16, %ax
movw %ax, %ds
movw %ax, %es
movw %ax, %gs
movw %ax, %fs
movw %ax, %ss
movl $0x400000, %ebp
movl %ebp, %esp
sti
call kmain

.code16
cpu_halt:
movw $s_cpu_halt, %si
call bios_printzln
hlt

bios_printzln:
	movb $15, %ah
	int $16
	movb $3, %ah
	int $16
	testb %dl, %dl
	movb $14, %ah
	jz __bios_printzln_loop
	movb $'\n', %al
	int $16
	movb $'\r', %al
	int $16
__bios_printzln_loop:
	lodsb
	testb %al, %al
	jz __bios_printzln_end
	int $16
	jmp __bios_printzln_loop
__bios_printzln_end:
	ret

test_a20:
	movw $0xffff, %ax
	movw %ax, %es
	movb %es:0x510, %al
	movb 0x500, %bl
	movb $0xaa, %es:0x510
	movb $0x55, 0x500
	movb %es:0x510, %ah
	cmpb $0xaa, %ah
	movb %al, %es:0x510
	movb %bl, 0x500
	sete %al
	ret

s_boot_start: .asciz "boot: starting up..."
s_cpu_halt: .asciz "cpu: halt"
s_a20_givenup: .asciz "a20: unable to activate, given up"
s_read_boot_disk_failure: .asciz "disk: boot disk read failure"
gdt:
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
gdt_desc:
	.word gdt_desc - gdt - 1
	.long gdt

.org 510
.word 0xaa55
