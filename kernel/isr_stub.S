.extern isr_handler

.macro isr intno
.globl isr\intno
isr\intno:
	cli
	pushl $0
	pushl $\intno
	jmp isr_stub
.endm

.macro isr_ec intno
.globl isr\intno
isr\intno:
	cli
	pushl $\intno
	jmp isr_stub
.endm

.text

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr_ec 8
isr 9
isr_ec 10
isr_ec 11
isr_ec 12
isr_ec 13
isr_ec 14
isr 15
isr 16
isr_ec 17
isr 18
isr 19
isr 20
isr_ec 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr_ec 29
isr_ec 30
isr 31
isr 32
isr 33
isr 34
isr 35
isr 36
isr 37
isr 38
isr 39
isr 40
isr 41
isr 42
isr 43
isr 44
isr 45
isr 46
isr 47

isr_stub:
	pushal

	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	movw $16, %ax
	movw %ax, %ds
	movw %ax, %fs
	movw %ax, %es
	movw %ax, %gs

	call isr_handler

	popl %gs
	popl %fs
	popl %gs
	popl %ds

	popal
	addl $8, %esp
	sti
	iret
