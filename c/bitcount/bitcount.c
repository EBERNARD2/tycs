#include <assert.h>
#include <stdio.h>

int bitcount(int x );

int main() {
  assert(bitcount(0) == 0);
  assert(bitcount(1) == 1);
  assert(bitcount(3) == 2);
  assert(bitcount(8) == 1);
  // harder case:
  assert(bitcount(0xffffffff) == 32);
  return 0;
}


int bitcount(int x){
  int count = 0;

  // for every 32 bit number we'll go through each one to see if it is on.
  for (int i = 0; i < 32; i++){
    int on = x & 0x1;
    x >>= 1;
    count += on;
  }

  return count;
}