#include <stdio.h>
#define RADIUS 10

int main(void){

    float fraction, pi, radius_cubed, volume;

    fraction = 4.0f/3.0f;

    pi = 3.14;

    radius_cubed = RADIUS * RADIUS * RADIUS;

    volume = (fraction) * pi * radius_cubed;

    printf("%.5f", volume);
    return 0;
}