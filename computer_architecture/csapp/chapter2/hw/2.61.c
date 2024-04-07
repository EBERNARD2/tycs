#include <stdio.h>
#include <stdbool.h>


//evaluate to 1 if all of conditions are true:
// - any bit of x equals 1
// - any bit of x equals 0
// - any bit in the least significant byte equals 1
// - any bit in the most significant byte equals 0 
// recieving an int so 4 bytes
// for example given 0xFFFFFFFF returns false
// but given 0x7FFFF77 returns true 
// or 0x00111170 returns true 
// not allowed to use conditionals, loops, etc only bitwise operations
 
bool msb_valid(int x);
bool lsb_valid(int x);
bool conditions_met(int x);

int main(void){
  int test_1 = 0x00000000; 
  int test_2 = 0xFFFFFFFF;
  int test_3 = 0x7FFFF777; 
  int test_4 = 0x00111170;

  int result1 = conditions_met(test_1) && msb_valid(test_1) && lsb_valid(test_1);
  printf("Result 1 (1 if conditions met 0 if not): %d\n", result1);
  int result2 = conditions_met(test_2) && msb_valid(test_2) && lsb_valid(test_2);
  printf("Result 2 (1 if conditions met 0 if not): %d\n", result2);
  int result3 = conditions_met(test_3) && msb_valid(test_3) && lsb_valid(test_3);
  printf("Result 3 (1 if conditions met 0 if not): %d\n", result3);
  int result4 = conditions_met(test_4) && msb_valid(test_4) && lsb_valid(test_4);
  printf("Result 4 (1 if conditions met 0 if not): %d\n", result4);


  return 0;

}

bool conditions_met(int x){
  return !(x == 0x00000000 || x == 0xFFFFFFFF);
}

bool msb_valid(int x){
  //seperate msb 
  // value to shift - 24 bits or 3 in binary shifted 2 ** 3
  int shift_val = (sizeof(int) - 1) << 3;

  // shift x value 3 bytes to right... bring msb down
  int shift_msb = x >> shift_val;
  int isolated_msb = shift_msb & 0xFF;

  // if all values in msb are 1, then this is not a valid msb. 
  // we can check that by comparing the msb to 0xFF which is all 1s 
  return !(isolated_msb == 0xFF); 
}

bool lsb_valid(int x){
  // seperate lsb. zero everything else out 
  int isolated_lsb = x & 0xFF;
  //if all bits in lsb are 0 we know that the lsb is not valid. If there is a 1
  // somewhere we can compare the lsb to 0
  return !(isolated_lsb == 0x00);
}