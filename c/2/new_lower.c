#include <stdio.h>


int lower(int c);

int main(void)
{
  printf("%c", lower("A"));
  printf("%c", lower("C"));

  return 0;
}

int lower(int c)
{
  return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}
