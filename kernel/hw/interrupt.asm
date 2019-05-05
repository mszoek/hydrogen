; Defined in isr.c
[extern isrHandler]
[extern irqHandler]

; Common ISR code
isrCommonStub:
    ; 1. Save CPU state
;	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    push rdi;
    push rsi;
    push rbp;
    push rsp;
    push rbx;
    push rdx;
    push rcx;
    push rax;
	mov ax, ds ; Lower 16-bits of eax = ds.
	push rax ; save the data segment descriptor
	mov ax, 0x10  ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

    ; 2. Call C handler
	call isrHandler

    ; 3. Restore state
	pop rax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
;	popa
    pop rax;
    pop rcx;
    pop rdx;
    pop rbx;
    pop rsp;
    pop rbp;
    pop rsi;
    pop rdi;
	add rsp, 0x10 ; Cleans up the pushed error code and pushed ISR number
	sti
	iretq ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; Common IRQ code. Identical to ISR code except for the 'call'
; and the 'pop ebx'
irqCommonStub:
;    pusha
    push rdi;
    push rsi;
    push rbp;
    push rsp;
    push rbx;
    push rdx;
    push rcx;
    push rax;
    mov ax, ds
    push rax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call irqHandler ; Different than the ISR code
    pop rbx  ; Different than the ISR code
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
;    popa
    pop rax;
    pop rcx;
    pop rdx;
    pop rbx;
    pop rsp;
    pop rbp;
    pop rsi;
    pop rdi;
    add rsp, 0x10
    sti
    iretq

; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.

; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr128

; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isrCommonStub

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isrCommonStub

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isrCommonStub

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isrCommonStub

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isrCommonStub

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isrCommonStub

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isrCommonStub

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isrCommonStub

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isrCommonStub

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isrCommonStub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isrCommonStub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isrCommonStub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isrCommonStub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isrCommonStub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isrCommonStub

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isrCommonStub

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isrCommonStub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isrCommonStub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isrCommonStub

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isrCommonStub

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isrCommonStub

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isrCommonStub

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isrCommonStub

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isrCommonStub

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isrCommonStub

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isrCommonStub

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isrCommonStub

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isrCommonStub

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isrCommonStub

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isrCommonStub

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isrCommonStub

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isrCommonStub

; --- SOFTWARE INTERRUPTS ---
; 128: syscall
isr128:
    cli
    push byte 0
    push byte 128
    jmp isrCommonStub

; IRQ handlers
irq0:
	cli
	push byte 0
	push byte 32
	jmp irqCommonStub

irq1:
	cli
	push byte 1
	push byte 33
	jmp irqCommonStub

irq2:
	cli
	push byte 2
	push byte 34
	jmp irqCommonStub

irq3:
	cli
	push byte 3
	push byte 35
	jmp irqCommonStub

irq4:
	cli
	push byte 4
	push byte 36
	jmp irqCommonStub

irq5:
	cli
	push byte 5
	push byte 37
	jmp irqCommonStub

irq6:
	cli
	push byte 6
	push byte 38
	jmp irqCommonStub

irq7:
	cli
	push byte 7
	push byte 39
	jmp irqCommonStub

irq8:
	cli
	push byte 8
	push byte 40
	jmp irqCommonStub

irq9:
	cli
	push byte 9
	push byte 41
	jmp irqCommonStub

irq10:
	cli
	push byte 10
	push byte 42
	jmp irqCommonStub

irq11:
	cli
	push byte 11
	push byte 43
	jmp irqCommonStub

irq12:
	cli
	push byte 12
	push byte 44
	jmp irqCommonStub

irq13:
	cli
	push byte 13
	push byte 45
	jmp irqCommonStub

irq14:
	cli
	push byte 14
	push byte 46
	jmp irqCommonStub

irq15:
	cli
	push byte 15
	push byte 47
	jmp irqCommonStub
