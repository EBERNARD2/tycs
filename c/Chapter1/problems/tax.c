#include <stdio.h>
#define TAX .05
int main(void){
    float amount;

    printf("Enter amount: ");
    scanf("%f", &amount);

    float total = (amount * TAX) + amount;
    printf("With tax added: $%.2f\n", total);

    return 0; 
}