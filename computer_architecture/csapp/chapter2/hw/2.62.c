#include <stdio.h>

int shifts_are_arithmetic(int x);

int main(void){
    
}

int shifts_are_arithmetic(int x){
    // if machine supports arithmetic right shifts when MSB is 1 th
    // need to figure out word size problem though 
    int check_right_shift = (x >> 30) & 0xFF; 

}