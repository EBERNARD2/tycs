#include <stdio.h>

#define swap(t, x, y) \
{                     \
  t temp;             \
  temp = x;              \
  x = y;              \
  y = temp;           \
};                    


int main(void)
{
  int x, y;

  x = 8;
  y = 200;
  swap(int, x, y);
  printf("x: %d \t\t y: %d\n", x, y);

  return 0;
}