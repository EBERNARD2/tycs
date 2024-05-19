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
(LOOP)
  // check if there is a value in keyboard register
  @KBD
  D=M
  // restart loop if there isn't a value
  @LOOP
  D;JEQ

  // turn screen black
  @SCREEN
  M=-1


  @LOOP
  0;JMP