#include <stdint.h>
#include <stdio.h>
#include <signal.h>

#define MEMORY_MAX (1 << 16)

enum 
{

  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC, /* Program counter*/
  R_COND,
  R_COUNT

};

enum 
{
  OP_BR = 0, /* BRANCH OP*/
  OP_ADD, /* ADD OP*/
  OP_LD, /* LOAD OP*/
  OP_ST, /* STORE OP*/
  OP_JSR, /* JUMP REGISTER*/
  OP_AND, /* AND OP*/
  OP_LDR, /*LOAD REGISTER*/
  OP_STR, /* STORE REGISTER*/
  OP_RTI, /* unused */
  OP_NOT, /* NOT OP*/
  OP_LDI, /* LOAD INDIRECT OP*/
  OP_STI, /* STORE INDIRECT OP*/
  OP_JMP, /* JUMP OP*/
  OP_RES, /* RESERVED */
  OP_LEA, /* LOAD EFFECTIVE ADDRESS OP*/
  OP_TRAP, /* execute trap */
};


enum 
{
  FL_POS = 1 << 0,
  FL_ZRO = 1 << 1,
  FL_NEG = 1 << 2
};


uint16_t memory[MEMORY_MAX];
uint16_t reg[R_COUNT];


uint16_t sign_extend(uint16_t x, int bit_count){
  // if it is a negative number (MSB is 1) than add additional 1s to keep number negative
  if ((x >> bit_count - 1) & 1){
    x |= (0xFFFF << bit_count); 
  }

  return x;
}

uint16_t mem_read(uint16_t address){
  return memory[address];
}

void update_flags(uint16_t r){
  if (reg[r] == 0){
    reg[R_COND] = FL_ZRO;
  } else if (reg[r] >> 15) { // if MSB is 1
    reg[R_COND] == FL_NEG;
  } else {
    reg[R_COND] == FL_POS;
  }
}

int main(int argc, const char* argv[]){
  // load arguments

  // setup
  if (argc < 2){
    pritnt('lc3 [file] ...\n');
    exit(2);
  }

  for (int j = 1; j < argc; ++j){
    //read image 
  }

  enum { PC_START = 0x3000 };
  reg[R_PC] = PC_START;

  int running = 1;

  while(running){

    // read instruction from memmory
    uint16_t instruction = mem_read(reg[R_PC]++);
    // get the operation 
    u_int16_t op = instruction >> 12;

    switch(op){
      case OP_ADD:
        
      break;

      case OP_AND:

      break;
    }

  }
}
