#include <stdint.h>
#include <stdio.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

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

u_int16_t reg[R_COUNT];

enum 
{
  OP_BR, /* BRANCH OP*/
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

