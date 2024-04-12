#include <stdio.h>

#define TMAX 2147483647
#define TMIN -2147483648

int saturating_add(int x, int y);

int main(void){

  saturating_add(214748, 2147483647);
  return 0;
}

int saturating_add(int x, int y){ 
  int mask = 1 << 31;
  int msb_x = mask & x;
  int msb_y = mask & y;

  // we know if there is positive overflow if x > 0 and y > 0 but their result is 0 or negative
  // we know there is negative overflow if x < 0 and y < 0 but their result is 0 or positive 
  // so basically we know something is up if the msb changes in either cases 
  int result = x + y ; 

  printf("result overflown: %x\n", result);


  return result ;

  
}