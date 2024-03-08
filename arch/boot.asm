bits 32

section .multiboot
align 8
multiboot_header:
dd 0xE85250D6
dd 0
dd multiboot_header_end - multiboot_header
dd -(0xE85250D6 + 0 + (multiboot_header_end - multiboot_header))
dw 0
dw 0
dd 8
multiboot_header_end:

section .bss
align 4096
stack_bottom:
resb 16384
stack_top:

pml4table:
resb 4096
pdpt:
resb 4096
pd:
resb 4096
pt:
resb 4096

extern kernel_init

global _start
section .text

_start:
    mov esp, stack_top
    cli

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov eax, pdpt
	or eax, 0b11 ; present, writable
	mov [pml4table], eax
	
	mov eax, pd
	or eax, 0b11 ; present, writable
	mov [pdpt], eax

	mov ecx, 0 ; counter
.loop:

	mov eax, 0x200000 ; 2MiB
	mul ecx
	or eax, 0b10000011 ; present, writable, huge page
	mov [pd + ecx * 8], eax

	inc ecx ; increment counter
	cmp ecx, 512 ; checks if the whole table is mapped
	jne .loop ; if not, continue

    mov eax, pml4table
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    call kernel_init

    cli
.hang:
    hlt
    jmp .hang

global load_gdtr
load_gdtr:
    mov eax, [esp+4]
    lgdt [eax]
    ret