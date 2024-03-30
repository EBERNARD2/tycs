#include <stdio.h>

/*
    This proggram breaks down an ISBN number by section by section
    Given an ISBN input (a number) -> A breakdown of GS1, Group
    Identifier, Publisher COde, Item Number, and Check Digit Sections
    given: 
        978-0-393-97950-3 as ISBN input
    expected:

        GS1 Prefix: 978
        Group Identifier: 0
        Publisher Code: 393
        Item Number: 97950
        Check Digit: 3

*/
int main(void){
    int gsi, group_identifier, publisher_code, item_number, check_digit;

    printf("Enter ISBN: ");
    scanf("%d-%d-%d-%d-%d", &gsi, &group_identifier, &publisher_code, &item_number, &check_digit);

    printf("GS1 Prefix: %d\n", gsi);
    printf("Group Identifier: %d\n", group_identifier);
    printf("Publisher Code: %d\n", publisher_code);
    printf("Item Number : %d\n", item_number);
    printf("Check Digit: %d\n", check_digit);
    return 0;

}