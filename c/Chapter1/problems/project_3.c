#include <stdio.h>

int main(void){

    float fraction, pi, radius_cubed, volume, radius;

    printf("Please enter radius of a sphere: \n");
    scanf("%f", &radius);

    fraction = 4.0f/3.0f;

    pi = 3.14;

    radius_cubed = radius * radius * radius;

    volume = (fraction) * pi * radius_cubed;

    printf("%.2f", volume);
    return 0;
}