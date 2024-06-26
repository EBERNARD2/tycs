#include <stdio.h>
#include <assert.h>


/*
  Exercise 2-6. Write a function setbits(x,p,n,y)
   that returns x with the n bits that begin at position 
   p set to the rightmost n bits of y, leaving the other bits unchanged.


  p = 4 && n = 3

  0000
  1101 
  1101 >> 3 = 110

  add that to right most bits of y

  example using chars

  x 
  001101010

  y 
  11001010

  p = 5


  n = 2


  so basically we are taking the two right most bits from position 5 of x and adding it to the end of y

  x >> (p + 1 - n)  so in our example this should turn into 000011010

  now we need to get p bits

  We could use & with a bitmask 0x1 shifted n - 1 times 

  so 1 shifted n - 1 (in our example) would shift to 10 then we shift back n - 1 times so we get 11 

  Then & that with the new x we calculated

  then all we need to do is & that result with y 


*/

int setbits(int x, int y, int n, int p);

int main(void)
{

  int x = setbits(4, 20, 4, 3);

  printf("Set bits, %d", x);
  
  return 0;
}

int setbits(int x, int y, int p, int n) 
{
  int shifted_x = (x >> (p+1-n)) & ~(~0 << n);

  return shifted_x & y;
}
