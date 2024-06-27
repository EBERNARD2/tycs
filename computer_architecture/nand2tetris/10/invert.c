#include <stdio.h>

int invertbits(int x, int p, int n);

int main(void)
{
  printf("invert:\n", (4, 20, 4, 3));

  return 0;
}

int invertbits(int x, int p, int n) 
{
  return ~((x >> (p+1-n)) & ~(~0 << n));
}