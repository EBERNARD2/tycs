#include <stdio.h>
#include <stdbool.h>

#define MAX_ARR 10

int main(void)
{
  bool digit_seen[MAX_ARR] = {false};
  int digit_count[MAX_ARR] = {0};
  bool first_repeated_digit = true;
  int digit;
  long n;


  printf("Enter a number: ");
  scanf("%ld", &n);


  while (n > 0) {
    digit = n % 10;

    if (digit_seen[digit])
      digit_count[digit]++;
    else 
      digit_seen[digit] = true;

    n /= 10;
  }

  for (int i = 0; i < MAX_ARR; i++) {
    if (digit_count[i] > 1) {
      if (first_repeated_digit) {
        printf("Repeated digit(s): ");
        first_repeated_digit = false;
      }

      printf(" %d ", i);
    }
  }


  if (first_repeated_digit)
    printf("No repeated digit\n");
   
  
  printf("\n");
 
  return 0;

}

