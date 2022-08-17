	.syntax		unified
	.cpu		cortex-m4
	.text


// void MatrixMultiply(int32_t A[3][3], int32_t B[3][3], int32_t C[3][3])
        .global		MatrixMultiply ;
        .thumb_func

MatrixMultiply:
        PUSH    {R4-R11,LR}
        LDR   R4,=0 //row number

        MOV   R9,R0  //A array
        MOV   R10,R1 //B array
        MOV   R11,R2  //C array



loopRow:
	CMP   R4,3  //If row >=3 we exit.
	BGE   ExitProgram
	LDR   R5,=0 //Col = 0

loopCol:
        CMP   R5,3 //If col<=3 stop looping columns.
        BGE   ExitColLoop 
        LDR   R6,=0//k number
        LDR   R0,=3//constant for calculation

        //Address of A[row][col] = original address of A  + 4 * (3*row + col)
        MUL   R7,R4,R0 //3 * row
        ADD   R7,R7,R5 //3 * row + col
        LDR   R0,=4
        MLA   R7,R7,R0,R9 //(3*row + col) * 4 is in R7 
        LDR   R0,=0
        STR   R0,[R7] //A[r][c] is set to 0

loopK:  
        CMP   R6,3
        BGE   ExitKLoop

        //B(row,k)address: 4*(3 * row  + k) + ptrB
        LDR   R0,=3
        MUL   R0,R4,R0	//3 * row 
        ADD   R0,R0,R6  //3 * row + k
        LDR   R8,=4  
        MLA   R1,R8,R0,R10   //(3 * row + l)*4 is held in R1
        LDR   R1,[R1]


        //C(k,col)address: 4* (3*k + col) + ptrA
        LDR   R0,=3 
        MUL   R0,R0,R6 //3 * k
        ADD   R0,R0,R5 // 3 * k + col
        MLA   R2,R8,R0,R11 // (3 * k + col)*4  is held in R2
        LDR   R2,[R2]

        MOV   R0,R7   //A[r][c] is now the first parameter for MultAndAdd 
        LDR   R0,[R0]

        BL    MultAndAdd
        STR   R0,[R7]   //results are put back into A[r][c]

        ADD   R6,R6,1 //increment k
        B    loopK

//increment columns
ExitKLoop:
        ADD   R5,R5,1 
        B     loopCol


//increment rows
ExitColLoop:
        ADD R4,R4,1 
        B  loopRow

//Exit MatrixMultiply
ExitProgram:
        POP   {R4-R11,PC}

.end
