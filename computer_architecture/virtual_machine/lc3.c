#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h> 



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

enum {
  TRAP_GETC = 0x20, /* get character from keyboard, not echoed onto the terminal */
  TRAP_OUT = 0x21, /* output a character */
  TRAP_PUTS = 0x22, /* output a word string */
  TRAP_IN = 0x23, /* get character from keyboard, echoed onto the terminal */
  TRAP_PUTSP = 0x24, /* output a byte string */
  TRAP_HALT = 0x25  /* halt the program */
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

void mem_write(uint16_t address, uint16_t val){
  memory[address] = val;
}

struct termios original_tio;

void disable_input_buffering()
{
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

uint16_t check_key()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
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

    // operation instruction bit values comes from resource: https://www.jmeiners.com/lc3-vm/supplies/lc3-isa.pdf
    switch(op){
      case OP_ADD:
        // get destination register
        uint16_t dest = (instruction & 0x0E00) >> 9;

        // get source register 1
        uint16_t src1 = (instruction & 0x01C0) >> 6;

        // determine if it is an immediate value or has source register 2
        uint16_t src2 = 0x0000; 

        uint16_t immediate = ( instruction & 0x0020 ) >> 5;

         if (immediate){
          // if has immediate value get value and convert to 16 bit int
          uint16_t immediate_val = instruction & 0x1F; 
          
          src2 = sign_extend(immediate_val, 5);

        } else { 
          // if has src 2 get address 
          src2 = instruction & 0x7; 
        }
      
        reg[dest] = reg[src1] + (immediate ? src2 : reg[src2]);
        update_flags(dest);

      break;

      case OP_AND:
        uint16_t dest = (instruction >> 9) & 0x7;
        uint16_t src1 = (instruction >> 6) & 0x7;
        uint16_t imm = (instruction >> 5) & 0x1;

        if (imm) {
          uint16_t imm_val = instruction & 0x1F;

          imm_val = sign_extend(imm_val, 5);

          reg[dest] = src1 & imm_val;
        } else {
          uint16_t src2 = instruction & 0x7; 

          reg[dest] =  reg[src1] & reg[src2];
        }

        update_flags(dest);

      break;

      case OP_BR:
        uint16_t n = (instruction >> 11) & 0x1;
        uint16_t z = (instruction >> 10) & 0x1;
        uint16_t p = (instruction >> 9) & 0x1;

        uint16_t jmp = n || z || p; 

        if (jmp & R_COND){

          uint16_t offset = instruction & 0x1FF;
          reg[R_PC] += sign_extend(offset, 9);
        }

      break;

      case OP_NOT: 
        uint16_t dest = (instruction >> 9) & 0x7;
        uint16_t src = (instruction >> 6) & 0x7;

        reg[dest] = ~reg[src];
        update_flags(dest);

      break;

      case OP_LDI:
        uint16_t dest = (instruction >> 9) & 0x7; 
        uint16_t pc_offset = sign_extend(instruction & 0xFF, 9);
        
        reg[dest] = mem_read(mem_read(reg[R_PC] + pc_offset));
        update_flags(dest);

      break;


    case OP_JSR:
      reg[R_R7] = reg[R_PC];
      uint16_t selection_bit  = (instruction >> 11) & 0x1;

      if (selection_bit){
        uint16_t offset = sign_extend((instruction & 0x7FF), 11);
        reg[R_PC] += offset;
      } else {
        uint16_t base_reg = (instruction >> 6) & 0x7;
        reg[R_PC] = reg[base_reg];
      }

    break;

    case OP_LD:
      u_int16_t dest = (instruction >> 9) & 0x7;
      u_int16_t offset = sign_extend(instruction & 0x1FF, 9);
      reg[dest] = mem_read(reg[R_PC] + offset);
      update_flags(dest);

    break;

    case OP_LDR:
      uint16_t dest = (instruction >> 9) & 0x7;
      uint16_t base_reg = (instruction >> 6) & 0x7;
      uint16_t offset = sign_extend(instruction & 0x3F, 6);

      reg[dest] = mem_read(reg[base_reg] + offset);

      update_flags(dest);
    break;

    case OP_LEA:

      uint16_t dest = (instruction >> 9) & 0x7;
      uint16_t offset = sign_extend(instruction & 0x1FF, 9);

      reg[dest] = reg[R_PC] + offset;
      update_flags(dest);
    break;

    case OP_ST:
      uint16_t src = (instruction >> 9) & 0x7;
      uint16_t offset = sign_extend(instruction & 0x1FF, 9);
      mem_write(reg[R_PC] + offset, reg[src]);

    break;

    case OP_STI:
      uint16_t src = (instruction >> 9) & 0x7;
      uint16_t offset = sign_extend(instruction & 0x1FF, 9);

      mem_write(mem_read(reg[R_PC] + offset), reg[src]);
    break;

    case OP_STR:
      uint16_t src = (instruction >> 9) & 0x7;
      uint16_t base_reg = (instruction >> 6) & 0x7;
      uint16_t offset = instruction & 0x3F;

      mem_write(reg[base_reg] + offset, reg[src]);
    break;

    case OP_TRAP:
      reg[R_R7] = reg[R_PC];

      switch (instruction & 0xFF)
      {

      case TRAP_GETC:
        /* code */
        reg[R_R0] = (uint16_t) getchar();
        update_flags(R_R0);
        break;
      
      case TRAP_OUT:

        uint16_t c = reg[R_R7];
        putc((char) c, stdout);
        fflush(stdout);

      break;

      case TRAP_PUTS:
        uint16_t *c = memory + reg[R_R0];

        while(*c){
          putc((char)*c, stdout);
          ++c;
        }

        fflush(stdout);
      break;

      case TRAP_IN:

      break;

      case TRAP_PUTSP:

      break;

      case TRAP_HALT:

      break;

      }
    break;

    case OP_RES:
    break;

    case OP_RTI:
    break;

    default:
      abort();
    break;

  }
}

restore_input_buffering();
