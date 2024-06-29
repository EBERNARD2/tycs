#include <stdio.h>


int bitcount(int x);


int main(void)
{
  
  printf("%d\n", bitcount(15));
  return 0;
}

int bitcount(int x)
{
  int b = 0;

  for (; x != 0; x &= (x - 1))
    b++;
  
  return b;
}

