 #include <stdio.h>
 #include <assert.h>


int odd_ones(unsigned x);

int main(void){
  assert(odd_ones(3) == 0);
  assert(odd_ones(0xFFFFFFFF) == 0);
  assert(odd_ones(0x00000001) == 1);
  printf("No errors\n");
  return 0;
}

int odd_ones(unsigned x){
  x ^= (x >> 16);
  x ^= (x >> 8);
  x ^= (x >> 4);
  x ^= (x >> 2);
  x ^= (x >> 1);
  return x & 0x01;
}