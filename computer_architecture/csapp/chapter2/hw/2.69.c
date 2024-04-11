#include <stdio.h>
#include <assert.h>

unsigned rotate_left(unsigned x, int n);

int main(void){

    unsigned og = 0x12345678;

    assert(rotate_left(og, 4) == 0x23456781);
    assert(rotate_left(og, 20) == 0x67812345);

    return 0;
}

// For bit wrapparound 0x12345678 n = 20 -> 0x67812345
unsigned rotate_left(unsigned x, int n){
    // first sift original number by n
    unsigned left_shift = x << n;

    // to get wraparound values we need to shift og number to the right 
    // 31 (representing unsigned int size) minus n times
    unsigned right_shift = x >> (31 - n) >> 1; 

    return left_shift | right_shift; 
}