#include <stdio.h>

int main(void){
    int d, f1, f2, f3, f4, f5, s1, s2, s3, s4, s5, 
        check, total, first_sum, second_sum;
    



    printf("Enter first (single) digt: ");
    scanf("%d", &d);
    printf("Enter first group of 5 digits: ");
    scanf("%1d%1d%1d%1d%1d", &f1, &f2, &f3, &f4, &f5);
    printf("Enter second group of 5 digits: "); 
    scanf("%1d%1d%1d%1d%1d", &s1, &s2, &s3, &s4, &s5);
    printf("Check digit: ");
    scanf("%1d", &check);

    first_sum = d + f2 + f4 + s1 + s3 + s5;
    second_sum = f1 + f3 + f5 + s2 + s4;

    total = ((first_sum * 3) + second_sum);


    printf("Check digit total %d\n", 9 - ((total - 1) % 10));


    return 0;

}