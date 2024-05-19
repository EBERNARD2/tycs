// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// screen starts at address RAM[16384] or just call screen 
// 

(INIT)
  @8192 // this is the register that maps back to the end of the screeen 
  D=A
  @i
  M=D

(LOOP)
  @i
  M=M-1
  @INIT
  M;JLT
  // get value in keyboard
  @KBD
  D=M
  // if value is zero turn screen white
  @WHITE
  D;JEQ
  // if there is a value turn screen black
  @BLACK
  0;JMP

  (WHITE)
    // grab correct register address
    @SCREEN
    D=A
    @i
    A=D+M
    M=0
    @LOOP
    0;JMP

  (BLACK)
    @SCREEN
    D=A
    @i
    A=D+M
    M=-1
    @LOOP
    0;JMP