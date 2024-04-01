#include <stdio.h>



int main(void){
    int input, hundreds, tens; 

    printf("Enter a three digit number: ");
    scanf("%3d",&input);

    hundreds = input % 100; 
    input /= 10;
    tens = input % 10;
    input /= 10;

    printf("The reversal is %d", (hundreds * 100) + (tens * 10) + input);

    return 0;


   
}