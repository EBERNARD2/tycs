#include <stdio.h>

int div16(int32_t num);

int main(void){
    int32_t test = -30;
    test = div16(test);

    printf("testing %d\n", test);
    return 0;
}



int div16(int32_t num){


    return num >> 4;
}


