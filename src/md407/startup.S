    .globl _start
    .section .start_section, "ax", %progbits
_start:
    ldr r0, =stack_top
    mov sp, r0
    bl main
    b .
