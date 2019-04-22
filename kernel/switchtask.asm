global switchTask
extern curTask
extern readyToRunStart
extern readyToRunEnd
extern taskSwitchSpinlock
extern taskSwitchWasPostponed

bits 64
section .text
align 8

switchTask:
; check whether switches are postponed
    push rax
    mov rax, taskSwitchSpinlock
    cmp DWORD [rax], 0
    je .notLocked
    mov rax, taskSwitchWasPostponed
    mov DWORD [rax], 1
    pop rax
    ret

.notLocked:
    pop rax
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
    mov [rsi+12], rsp       ; save sp in curTask TCB slot
    cmp BYTE [rsi+36], 1    ; still in 'running' state?
    jne .notRunning
    mov BYTE [rsi+36], 0    ; put in 'ready to run'
    mov rax, readyToRunEnd  ; get end of run list
    mov rdx, [rax]          ; value of variable
    cmp rdx, 0              ; null?
    je .noAppend
    mov rsi, [rax]
    mov rdx, [rbx]
    mov [rsi], rdx          ; list end->next = curTask

.noAppend:
    mov [rax], rdx          ; curTask is now end of list
    mov rax, readyToRunStart
    mov rsi, [rax]
    cmp rsi, 0
    jne .notRunning
    mov [rax], rdx          ; set list start to curTask too since it was empty

.notRunning:
    mov [rbx], rdi          ; curTask = what we passed in
    mov rsp, [rdi+12]       ; load sp for new task
    mov rax, [rdi+28]       ; load cr3 for new task
    mov BYTE [rdi+36], 1    ; set 'running' state
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
