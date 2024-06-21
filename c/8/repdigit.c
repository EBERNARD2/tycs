#include <stdio.h>
#include <stdbool.h>

#define MAX_ARR 10

int main(void)
{
  bool digit_seen[MAX_ARR] = {false};
  bool first_repeated_digit = true;
  int digit;
  long n;

  printf("Enter a number: ");
  scanf("%ld", &n);


  while (n > 0) {
    digit = n % 10;
    n /= 10;

    if (digit_seen[digit]) {

      if (first_repeated_digit) {
        printf("Repeated digit(s)");
        first_repeated_digit = false;
      }

      printf("%6d", digit);
      continue;
    }

    digit_seen[digit] = true;

  }

  if (first_repeated_digit)
    printf("No repeated digit\n");
   
 
  return 0;

}

