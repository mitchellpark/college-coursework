
	.syntax		unified
	.cpu		cortex-m4
	.text

	.global		Add
	.thumb_func

//Adds two int32_t parameters, and the sum is stored in R0. 
Add:
	ADD R0, R0, R1
	BX LR

	.global		Less1
	.thumb_func

//Subtracts 1 from R0, and the results is stored in R0.
Less1:
	SUB R0, R0, 1
	BX LR

	.global		Square2x
	.thumb_func

//R0's value is double, and then it is a parameter for calling function Square
Square2x:
	ADD R0, R0, R0
	B Square

	.global		Last
	.thumb_func


//Static variable R4 holds the value of x. Adding R0 and R4 is equivalent to x + SquareRoot(x).
Last:
	PUSH {R4, LR}
	MOV R4, R0
	BL SquareRoot
	Add R0, R4, R0
	POP {R4, LR}
	BX LR

	.end
