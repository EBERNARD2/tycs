#include <stdio.h>


int main(void){
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    // get least significant byte of x
    int lsb = x & 0x000000FF;

    //create new number that copies 3 bytes from int y then LSB from int x
    int n = 0;
    int counter = 0;


    int all_but_lsb = y & 0xFFFFFF00;


    int num = all_but_lsb + lsb;

    printf("New Num %X\n", num);

    return 0;

}