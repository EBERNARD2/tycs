#include <stdio.h>
#include <stdbool.h>

bool little_endian_machine();

int main(void){

    bool is_le = little_endian_machine();

    printf("Is Little Endian Machine? (1 if Yes 0 if no) \t %d\n", is_le);

    return 0;
}

bool little_endian_machine(){
    int x = 1;
    int * address_pointer;
    address_pointer = &x;
    printf("Value of first byte of 4 byte integer - 1: %d\n", address_pointer[0]);
    
    return address_pointer[0] == 0x01;
}