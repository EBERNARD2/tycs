#include <stdio.h>

int leftover(int amount, int bill);

int main(void){
    int dollar_amount, remaining_balance; 

    printf("Enter a dollar amount: ");
    scanf("%d", &dollar_amount);

    printf("$20 bills: %d\n", dollar_amount/20);
    remaining_balance = leftover(dollar_amount, 20);

    printf("$10 bills %d\n", remaining_balance / 10);
    remaining_balance = leftover(remaining_balance, 10);

    printf("$5 bills %d\n", remaining_balance / 5);
    remaining_balance = leftover(remaining_balance, 5);

    printf("$1 bills %d\n", remaining_balance / 1);
    
    return 0; 
}

int leftover(int amount, int bill){
    return amount % bill;
}