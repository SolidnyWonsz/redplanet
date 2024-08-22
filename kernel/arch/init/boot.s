.set ALIGN,		1<<0
.set MEMINFO,	1<<1
.set FLAGS,		ALIGN | MEMINFO
.set MAGIC,		0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp

	/*
	Since Red Planet has moved to C++, paging, GDT, global constructors,
	floating point instructions and exceptions must be initialized here.
	*/

	push %ebx
	call kernel_init

	cli
1:	hlt
	jmp 1b

.size _start, . - _start

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	jmp $0x08, $reload
reload:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret
