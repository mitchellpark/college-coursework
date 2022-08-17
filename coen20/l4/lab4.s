

        .syntax     unified
        .cpu        cortex-m4
        .text


.global UseLDRB
.thumb_func
.align


//transferring 512 bytes, one byte at a time. We load and store 512 times.
UseLDRB:
        .rept 512
        LDRB R3, [R1], 1 
        STRB R3, [R0], 1  
        .endr

        BX LR


.global UseLDRH
.thumb_func
.align

//we load and store 256 times, because we are transferring 2 bytes at a time.
UseLDRH:
        .rept 256  
        LDRH R3, [R1], 2  
        STRH R3, [R0], 2
        .endr

        BX LR


.global UseLDR
.thumb_func
.align

//We load and store 128, because we transfer 4 bytes at a time.
UseLDR:
        .rept 128  
        LDR R3, [R1], 4  
        STR R3, [R0], 4
        .endr

        BX LR


.global UseLDRD
.thumb_func
.align

//We repeat the load-and-store process 64 times because we transfer 8 bytes at a time.
//Unlike the other functions,  need two registers to hold the size of 8 bytes.
UseLDRD:
        .rept 64  
        LDRD R3, R2, [R1], 8  
        STRD R3, R2, [R0], 8
        .endr

        BX LR


.global UseLDM
.thumb_func
.align

//We load and store 8 registers at a time, 16 times for 128 bytes. Here, we must push and pop R4-R9 to 
//use them; we don't want the values changed in other functions.
UseLDM:
		PUSH {R4-R9}
		.rept	16 
		LDMIA	R1!, {R2-R9}
		STMIA	R0!, {R2-R9}
		.endr
		POP	{R4-R9}
		BX		LR
		.end
