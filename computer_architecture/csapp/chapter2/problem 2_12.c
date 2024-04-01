#include <stdio.h>


int main(void){
    // should work regardless of word length
    int part_a, part_b, part_c, x;

    x = 0x87654321;

    // print least significant byte
    part_a = 0xff & x; 
    printf("Here is the least significant byte: %X\n", part_a);

    // complement all bytes but leave least significant byte unchanged
    part_b = ~x;
    printf("Complemented Bytes with least significant bytes unchanged: %X\n", part_b ^ 0xff);


    // Least significant byte set to ones and all other bytes unchanged

    part_c = x | 0xff;

    printf("Least significant bytes set to ones - all other bytes left unchanged: %X\n", part_c);

    return 0;



}



