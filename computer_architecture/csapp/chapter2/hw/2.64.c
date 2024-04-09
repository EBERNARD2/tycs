#include <stdio.h>

int any_odd_one(unsigned x);

int main(void){
    printf("Testing func\n");
    printf("With 0x00000000 \t Result: %d\n", any_odd_one(0x00000000));
    printf("With 0xFFFFFFFF \t Result: %d\n", any_odd_one(0xFFFFFFFF));
    printf("With 0x00000002 \t Result: %d\n", any_odd_one(0x00000002));

    return 0;
}

int any_odd_one(unsigned x){
    return !!(x & 0xAAAAAAAA);
}
