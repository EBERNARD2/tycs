#include <stdio.h>
#define INCHES_PER_POUND 166 

int main(void){
    int height, width, length, volume, weight;

    printf("Enter height of box: " );
    scanf("%d", &height);
    printf("Enter width of box: ");
    scanf("%d", &width);
    printf("Enter length of box: ");
    scanf("%d", &length);

    volume = width * height * length;

    weight = (volume + INCHES_PER_POUND - 1) /INCHES_PER_POUND;


    printf("%d\n", weight);
    return 0;

}