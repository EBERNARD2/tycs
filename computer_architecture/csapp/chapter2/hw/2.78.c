#include <stdio.h>

int divide_power2(int x, int k);

int main(void){

}

int divide_power2(int x, int k){
  // divide x by 2**k
  // basically a right shift k times
  // but we need to be aware of the arithmetic shift filling in shifts with the msb.
  // example for 8 (1000) shifted 2**3 (8/8) we would expect 0001, But arithmetic right 
  // shifting will fill in new zeros with msb so it would be 1111 instead 

}
