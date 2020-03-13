/*
 * H2 Standard C Library - C runtime init
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

.section .init
    /* gcc will insert crtend .init here */
    popq %rbp
    ret

.section .fini
    /* gcc will insert crtend .fini here */
    popq %rbp
    ret
