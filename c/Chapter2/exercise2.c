#include <stdio.h>

int main(void){
    float x = 32.123000;

    printf("Left Justified in a field size of 8 with one digit after decimal: %8.1e\n", x);
    printf("Right Justified in a field size of 10 with six digits after decimal: %10.6e\n", x);
    printf("Left Justified in a field size of 8 with three digits after decimal: %8.3f\n", x);
    printf("Right Justified in a field size of 6 with one digit after decimal: %6.0f\n", x) ;
    return 0; 

}