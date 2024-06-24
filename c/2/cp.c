#include <stdio.h>

int main(void)
{

  short int t = 4;
  long int b = 4;

  printf("Size of t: %lu\n", (sizeof(t)));
  printf("Size of b: %lu\n", (sizeof(b)));

  return 0;
}