#include <stdio.h> 
#define FREEZE_POINT 32.00f
#define RATIO_OF_CHANGE (5.0f/9.0f)

int main(void){
    float farenheight, celcius;

    printf("Enter farenheight temperature: ");
    scanf("%f", &farenheight);
    
    celcius = (farenheight - FREEZE_POINT) * RATIO_OF_CHANGE;

    printf("Celcius Equivalent: %.1f\n", celcius);

    return 0;

    

}