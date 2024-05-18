// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// set r2 to zero 
@R2
M=0 

// If r0 is zero go to end
@R0
D=M
@END
D;JEQ
// if r1 is zero go to end
@R1
D=M
@END
D;JEQ

// Loop to add numbers
(LOOP)
// add r0 to sum 
@R0
D=M
@R2
D=D+M

//subtract 1 from r1
@R1
M=M-1

// if r1 is greater than zero run loop again 
D=M
@LOOP
D;JGT

(END)
@END
0;JMP