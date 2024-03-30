#include <stdio.h>

int main(void){
    int height, width, length, volume; 
    float profit, loss;


    height = 10;
    width = 30;
    length = 15;

    profit = 23455.00f;
    loss = 2344.54f; 

    volume = height * width * length; /* Volume is now XXXX */
    printf("Height: %d\n", height); 
    printf("Profit: $%.2f\n", profit);
    printf("Height: %d Length: %d, Width %d", height, length, width);
}