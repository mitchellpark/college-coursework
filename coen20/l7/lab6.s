.syntax         unified
.cpu            cortex-m4
.text


.global ReverseBits
.thumb_func
.align

ReverseBits:
	LDR R1, =0
	.rept 32
	LSLS R0, R0, 1	//shifting the register left one bit and setting the flag
	RRX R1, R1     //rotating the reverse string right and putting the carry in right spot
	.endr

	MOV R0, R1	//putting the reverse string back into R0
	BX LR

.global ReverseBytes
.thumb_func
.align

ReverseBytes:
	BFI R1, R0,  24, 8 	//takes the last 8 bits and moves it over 24 bits into R1
	LSR R0, R0, 8		// shift R0 right 8 bits
	BFI R1, R0, 16, 8      //takes the last 8 bits and moves it over 16 bits into R1
	LSR R0, R0, 8          //
	BFI R1, R0, 8, 8
	LSR R0, R0, 8
	BFI R1, R0, 0, 8
	MOV R0, R1
	BX LR

.end
