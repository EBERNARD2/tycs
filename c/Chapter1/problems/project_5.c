#include <stdio.h>

int power(int base, int raised);
int main(void){
    int x, poly_formula; 

    printf("Enter X: ");
    scanf("%d", &x);

    poly_formula = 3 * power(x, 5) + 2 * power(x, 4) - 5 * power(x, 3) - power(x, 2) + 7 * x - 6;

    printf("Value of polynomial: %d\n", poly_formula);

    return 0;


}

int power(int base, int raised){
    int sum = 1;

    for (int i = 0; i < raised; i++){
        sum *= base;
    } 

    return sum; 
}