#include <stdio.h> 

int main(void){
    int x = 53191;

    short sx = (short) x;
    int y = (int) sx;

    printf("sx = %X\n", x);
    printf("sx = %X\n", sx);
    printf("y = %X\n", y);
    printf("little endian: %X\n", (int) 120000);


    /// testing error with subtracting 2 unsigned numbers

    unsigned short t1 = 5;
    unsigned short t2 = 7;
    printf("t1 = %x\n",  t1);
    printf("t2 %x\n", t2);
    printf("test: %x\n", t1 - t2);

    return 0;
}