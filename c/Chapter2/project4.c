#include <stdio.h>

/*
    This program prompts user for telephone number input from user and returns number reformatted
    given: 
        (123) 456-7890
    expectd: 
        123.456.7890
*/

int main(void){
    int area_code, middle, ending;

    printf("Enter phone number (xxx) xxx-xxxx: ");
    scanf("(%d) %d-%d", &area_code, &middle, &ending);

    printf("You entered %d.%d.%d\n", area_code, middle,ending);
    return 0;

}