global switchUserland
extern curTask

; extern "C" void switchUserland(void)

[bits 64]
switchUserland:
    mov ax, 0x23    ; user DS (0x20) with bottom bits set for ring 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rax, curTask
    mov rsi, [rax]
    mov rax, [rsi+20] ; get usersp pointer
    push 0x23
    push rax        ; save stack pointer
    pushfq
    push 0x1B       ; user CS (0x18) with bottom bits set for ring 3
    push 0x600010   ; entry point of user code
    iretq
