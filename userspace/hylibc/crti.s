/*
 * H2 Standard C Library - C runtime init
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

.section .init
.global _init
.type _init, @function
_init:
    push %rbp
    movq %rsp, %rbp
    /* gcc will insert crtbegin .init here */

.section .fini
.global _fini
.type _fini, @function
_fini:
    push %rbp
    movq %rsp, %rbp
    /* gcc will insert crtbegin .fini here */
