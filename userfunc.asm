global userfunc

[bits 64]
[section .text]
org 0xfab0

userfunc:
    mov r10, 1
    lea r11, [string]
    mov r12, 0
    mov r13, 0
    mov r14, 0
    mov r15, 0
    int 0x80
    mov r10, 2
    xor r11, r11
    xor r12, r12
    xor r13, r13
    xor r14, r14
    xor r15, r15
    int 0x80
die: jmp die

string: db "Hello userspace!", 10, 0