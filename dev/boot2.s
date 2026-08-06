/* Multiboot header */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack */
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function

_start:
	movb $'X', %al
	outb %al, $0xe9

	mov $stack_top, %esp

	/* Direct VGA test: print A */
	mov $0xB8000, %edi
	movw $0x0F41, (%edi)

	movb $'Y', %al
	outb %al, $0xe9

	call kernel_main

	movb $'Z', %al
	outb %al, $0xe9

	cli
1:
	hlt
	jmp 1b

.size _start, . - _start
