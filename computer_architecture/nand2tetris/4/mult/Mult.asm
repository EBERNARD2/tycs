// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

////

@R2
M=0

@R1
D=M
@i 
M=D // Set i to r1

(LOOP)
  @i // check if i is 0
  D=M
  @END
  D;JLE

  // add r0 to r2
  @R0
  D=M
  @R2
  M=D+M
  // subtract 1 from i
  @i
  M=M-1
  @LOOP
  0;JMP

(END)
  @END
  0;JMP
