#include <stdio.h> 

/*
    This program formats product information submitted by user
    Item Number, Unit Price, Purchase Date --> Formated version of data
    given: 
        583 as item_number 
        13.5 as unit_price
        10/24/2010 as purchase_date

    expected: 
    Item            Unit           Purchase
                    Price          Date

    583             $ 13.50         10/24/2010       
*/

int main(void){
    int item_number, month, day, year;
    float unit_price;

    printf("Enter item number: ");
    scanf("%d", &item_number);
    printf("Enter unit price: ");
    scanf("%f", &unit_price);
    printf("Enter purchase date (mm/dd/yyyy): ");
    scanf("%d/%d/%d",/* Œ¸ */ &month, &day, &year);

    printf("Item\tUnit\tPurchase\n\tPrice\tDate\n");
    printf("%d\t$ %4.2f\t%d/%d/%d\n", item_number, unit_price, month,day,year);

    return 0;
}