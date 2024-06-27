#include <stdio.h>


/*

  Let's imagine we have a bit patern (we will make it simple with a char value)

  10101110

  if we rotate the value 5 positions to the right we should get:
  11101010

  So what do we know? 

  A char is 8 bits, we have n (the number of bits to shift)

  we're basically going to position n (5) and yanking those values to position 0 (without filling in bits on right shift)

  we'd then store that result in a variable 

  then on the other end we are taking the bit length (8 in this case) and subtracting the right shift from it
  so that we know what position to start the left shift. 
  
  Once we have that position we want to left shift the number that we originally shifted (n)


  so going back to our example:

  x= b10101110 , n = 5

  step 1 
  Right shift position n to position 0 

  After that step, x should be

  b


This is the naive example. We still need to consider what if the value is larger than data type size


*/
int main(void)
{

}