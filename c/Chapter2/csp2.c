#include <stdio.h>

int main(void){
    printf("%.2f\n", (3.14+1e20) - 1e20);
    printf("%.2f\n", 3.14+(1e20-1e20));
    return 0;
}