#include <stdio.h>


void i_toa(int n);

int main(void)
{
  i_toa(-256);
  printf("\n");
  i_toa(45);
  printf("\n");
  i_toa(-1006);
  printf("\n");
  return 0;
}


void i_toa(int n)
{

  if (n < 0)  {
    printf("-");
    n = -n;
  }

  if (n / 10) 
    i_toa(n / 10);
  
  printf("%d", n % 10);
}
