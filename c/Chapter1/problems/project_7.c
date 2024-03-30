#include <stdio.h>


float calculate_balence(float principle, float monthly_payment, float interest_rate); 

int main(void){
    float loan, interest_rate, monthly_interest_rate, monthly_payment, principle; 

    printf("Enter amount of loan: ");
    scanf("%f", &loan);
    printf("Enter interest rate: ");
    scanf("%f", &interest_rate);
    printf("Enter monthly payment: ");
    scanf("%f", &monthly_payment);

    monthly_interest_rate = (interest_rate / 100) / 12;

    principle = calculate_balence(loan, monthly_payment, monthly_interest_rate);

    printf("Balance remaining after first payment $%.2f\n", principle);

    principle = calculate_balence(principle, monthly_payment, monthly_interest_rate);

    printf("Balance remaining after second payment $%.2f\n", principle);

    principle = calculate_balence(principle, monthly_payment, monthly_interest_rate);

    printf("Balance remaining after third payment $%.2f\n", principle);

    return 0;
}


float calculate_balence(float principle, float monthly_payment, float interest_rate){
    return ((principle * interest_rate) + principle ) - monthly_payment;
}
