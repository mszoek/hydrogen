global switchTask
extern curTask

bits 64
section .text
align 8

switchTask:
; callq only pushes the return address, so save everything
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push rbp

    mov rbx, curTask
    mov rsi, [rbx]
    mov [rsi+12], rsp   ; save sp in curTask TCB slot

 ;   mov rsi, [rdi+0]    ; load 'next' pointer from TCB
    mov [rbx], rdi      ; curTask = what we passed in
    mov rsp, [rdi+12]   ; load sp for new task
    mov rax, [rdi+28]   ; load cr3 for new task
;    mov [TSS.rsp0], rbx
;    cmp rax, rcx
;    je .sameVAS
;    mov cr3, rax

.sameVAS:
    pop rbp             ; get regs from the new stack
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ret                 ; return to new task's saved IP
