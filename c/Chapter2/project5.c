#include <stdio.h>

/*
    This program prompts the user for unique values from 1 - 16 and returns two things:
       -  a display of numbers entered in 4 x 4 arrangement
       - Sums of each row, each columnn, and each diagnal in the arrangement

       given: 
        16 3 2 13 5 10 11 8 9 6 7 12 4 15 14 1
        
        expected:
            16 3 2 13
            5 10 11 8
            9 6  7 12
            4 15 14 1

            Row sums: 34 34 34 34 
            Column sums: 34 34 34 34 
            Dialgonal Sums: 34 34 
*/

int main(void){
    int one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen;

    printf("Enter the numbers from 1 to 16 in any order: \n");
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &one, &two, &three, &four, &five, &six, &seven, &eight, &nine, &ten, &eleven, &twelve, &thirteen, &fourteen, &fifteen, &sixteen);

    printf("\n%d %d %d %d\n", one, two, three, four);
    printf("%d %d %d %d\n", five, six, seven, eight);
    printf("%d %d %d %d\n", nine, ten, eleven, twelve);
    printf("%d %d %d %d\n", thirteen, fourteen, fifteen, sixteen);

    int row_one_sum = one + two + three + four;
    int row_two_sum = five + six + seven + eight;
    int row_three_sum = nine + ten + eleven + twelve;
    int row_four_sum = thirteen + fourteen + fifteen + sixteen;

    printf("\nRow Sums: %d %d %d %d\n", row_one_sum, row_two_sum, row_three_sum, row_four_sum);

    int columnn_one_sum = one + five + nine + thirteen;
    int columnn_two_sum = two + six + ten + fourteen;
    int columnn_three_sum = three + seven + eleven + fifteen; 
    int columnn_four_sum = four + eight + twelve + sixteen;

    printf("Row Sums: %d %d %d %d\n",columnn_one_sum, columnn_two_sum, columnn_three_sum, columnn_four_sum);


    int diagnal_one = one + six + eleven + sixteen;
    int diagnal_two = four + seven + ten + thirteen;

    printf("Diagonal sums %d %d\n", diagnal_one, diagnal_two);

    return 0;


}