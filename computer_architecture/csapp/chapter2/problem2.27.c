#include <stdio.h>
#include <math.h>

int uadd_ok(unsigned int x, unsigned int y);

int main(void){

    uadd_ok(4294967295u, 1u);

    return 0;
}


int uadd_ok(unsigned int x, unsigned int y){
    printf("x: %u\n", x);
    printf("y: %u\n", y);
    
    int sum = x + y;

    printf("sum: %u\n", sum);
    

    if (sum < x || sum < y){
        printf("overflow occured with num \t %u \t hex: %X\n", sum, sum);
        return 1;
    } 
    return 0;
}