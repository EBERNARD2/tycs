#include <stdio.h>

int main(void){
    int input, ones_place, tens_place;

    printf("Enter a two-digit number: ");
    scanf("%2d", &input);

    tens_place = input % 10;
    ones_place = input / 10;

    printf("The reversal is %d\n", (10 * tens_place) + ones_place);
    return 0;
}
   