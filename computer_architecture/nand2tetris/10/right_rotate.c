#include <stdio.h>
#include <assert.h>


int right_rotate(int x, int n);

int main(void)
{
  printf("%d\n", right_rotate(175, 5));
  return 0;
}

int right_rotate(int x, int n)
{
  int size, right, mask, logical_r_shift, left;

  size = (int) sizeof(x) * 8;

  right = n % size;
  
  logical_r_shift = (x >> right) & (0x1 << (size - 1)) >> (size - 1);

  left = x << (size - right);

  printf("left: %X right: %X\n", left, logical_r_shift);
  return logical_r_shift & left;
}
