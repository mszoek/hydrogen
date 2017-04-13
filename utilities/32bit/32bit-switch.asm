[bits 16]
switch_to_pm:
  cli ; 1. Disable interrupts
  lgdt [gdt_descriptor] ; 2. Load the GDT descriptor
  mov eax, cr0
  or eax, 0x1 ; 3. set 32-bit mode in cr0
  mov cr0, eax
  jmp CODE_SEG:init_pm ; 4. Jump far away by using a different segment

[bits 32]
init_pm:
  mov ax, DATA_SEG ; 5. update the segment registers
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x90000 ; 6. Update the stack right at the top of free space
  mov esp, ebp

  call BEGIN_PM ; 7. Call label with useful code
