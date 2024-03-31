#include <stdio.h>

int main(void){
    int mod = 7345;
    mod %= 22;

    printf("testing mod op %d\n", mod);

    return 0;
}