
    .syntax     unified
    .cpu        cortex-m4
    .text

// The TireDiam function computes the diameter of a tire, which is expressed as R + (AxW)/1270, with
//parameters W, A, R (Tire width, aspect ratio, and rim diameter.
    .global TireDiam
    .thumb_func

TireDiam:
    PUSH    {R4, LR}
    LDR     R3,=1270 

    MUL     R4,R0,R1 // (A x W) is stored in R4.
    UDIV    R0,R4,R3 //A x W / 1270 is stored in R1. Division is unsigned.
    ADDS    R1,R0,R2 // R + (A x W) / 1270. R1 holds the value of the quotient.
    MLS     R0,R3,R0,R4 // R0 holds the value of the remainder.

    POP     {R4, LR}

    BX      LR 

//The TireCirc function computes the circumference of tire, which is expressed as pi * d, where d is the diameter. 
    .global TireCirc
    .thumb_func

TireCirc:
    PUSH    {R4, R5, R6, LR}
    BL      TireDiam

    LDR     R2,=1587500 
    LDR     R3,=4987290
    LDR     R4,=3927

    MUL     R5,R4,R0 //3927 * remainder of TireDiam
    MLA     R6,R3,R1,R5 //Multiply and add: (4987290 * TireDiam) + (3927 * remainder of TireDiam) is stored in R6 
    UDIV    R1,R6,R2 // Unsigned division, R1 holds the quotient.
    MLS     R0,R2,R1,R6 // The remainder, (R6-(R2 * R1)) is held in R0. 

    POP     {R4, R5, R6, LR}

    BX      LR

    .end
