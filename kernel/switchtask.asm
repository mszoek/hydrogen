global switchTask
global initTasks

extern curTask
extern runQ
extern runQEnd
extern locksHeld
extern taskSwitchDeferred
extern tss
extern switchUserland

bits 64
section .text
align 8

switchTask:
    push rax
    mov rax, locksHeld
    cmp QWORD [rax], 0
    je .notLocked
    mov rax, taskSwitchDeferred
    mov DWORD [rax], 1
    pop rax
    ret

.notLocked:

    pop rax
; callq only pushes the return address, so save everything
    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push rbp

    mov rbx, curTask
    mov rsi, [rbx]
    mov [rsi+12], rsp       ; save sp in curTask TCB slot
    cmp BYTE [rsi+44], 1    ; still in 'running' state?
    jne .notRunning
    mov QWORD [rsi], 0      ; curTask->next = 0
    mov BYTE [rsi+44], 0    ; put in 'ready to run'
    mov rax, runQ           ; get start of run list
    mov rdx, [rax]
    cmp rdx, 0              ; start = null?
    je .noAppend

    mov rax, runQEnd        ; list end address
    mov rdx, [rax]          ; value
    mov [rdx], rsi          ; last_node->next = curTask
    mov [rax], rsi          ; list end = curTask
    jmp .notRunning

.noAppend:
    mov [rax], rsi          ; list start = curTask
    mov rax, runQEnd        ; list end address
    mov rdx, [rax]          ; value
    mov [rax], rsi          ; list end = curTask

.notRunning:
    mov [rbx], rdi          ; curTask = what we passed in
    mov rsp, [rdi+12]       ; load sp for new task
    mov QWORD [rdi+46], 1   ; set timeslice
    mov rax, [rdi+45]       ; task priority
    add [rdi+46], rax
    mov rbx, [rdi+28]       ; load kernel stack top of new task
    mov BYTE [rdi+44], 1    ; set 'running' state
    mov rax, [rdi+36]       ; load cr3 for new task
    mov rdx, tss
    mov rdi, [rdx]
    mov [rdi+4], rbx        ; save rsp0 into TSS for cpu0
    mov rcx, cr3
    cmp rax, rcx
    je .sameVAS
    mov cr3, rax
    

.sameVAS:
    pop rbp                 ; get regs from the new stack
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

    sti
    ret                     ; return to new task's saved IP


initTasks:
    mov rbx, curTask
    mov rsi, [rbx]
    mov rsp, [rsi+12]       ; load sp for new task
    mov rbp, rsp
    mov QWORD [rsi+46], 1
    mov rax, [rsi+45]       ; task priority
    add [rsi+46], rax
    mov rbx, [rsi+28]       ; load kernel stack top of new task
    mov BYTE [rsi+44], 1    ; set 'running' state
    mov rdx, tss
    mov rsi, [rdx]
    mov [rsi+4], rbx        ; save rsp0 into TSS for cpu0
    ret                     ; return to new task's saved IP
