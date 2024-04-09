#include <stdio.h>

int shifts_are_arithmetic();

int main(void){
    printf("Right shift arithmetic machine: %d\n", shifts_are_arithmetic());
    return 0;
}

int shifts_are_arithmetic(){
    // if machine supports arithmetic right shifts when MSB is 1 
    // during a right shift all values will be filled with 1
    // so we can left shift a one 32 bits and shift back to first bit.
    // if the new number is equal to the max int for a 32 bit machine 
    // we know the machine is using right shift arithmetic 
    int x = 0x1; 
    x <<= 31;
    x >>= 31;
    return x == 0xffffffff;
}