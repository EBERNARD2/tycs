#include <stdio.h>


int add_ok(int x, int y);

int main(void){

    int x = -2147483647 - 1;
    int y = -1;

    printf("Ok to add %d and %d? If 0 yes. If 1 No :%d\n", x, y, add_ok(x,y));

    return 0;
    
}


int add_ok(int x, int y){
    int sum = x + y;

    // if positive overflow
    if (x > 0 && y > 0 && sum <= 0 ) {
        printf("Sum %d has positive overflow. \t Hex: %X\n", sum, sum);
        return 1;
    } else if (x < 0 && y < 0 && sum >= 0){
        // if negative overflow
        printf("Sum %d has negative overflow. \t Hex: %X\n", sum, sum);

         return 1;
    }

    // normal two's complement addition 
    printf("Normal sum %d \t Hex: %X", sum, sum);

    return 0;
    
}