#include <stdio.h>
#include <assert.h>

int lower_one_mask(int m);

int main(void){
  assert(lower_one_mask(6) == 0x3f);
  assert(lower_one_mask(17) == 0x1ffff);
  printf("Ok\n");
  return 0;
}

int lower_one_mask(int m){
  int x = 0x01 << 31;
  int shift = 31 - m;
  x >>= shift;
  return ~(x & 0xFFFFFFFF);
}
