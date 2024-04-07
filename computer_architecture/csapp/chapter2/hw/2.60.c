#include <stdio.h>

unsigned replace_bytes(unsigned eight_bytes, int index, unsigned char replacement);

int main(void){

	int original_hex = 0x12345678;

	printf("replace bytes %X\n", replace_bytes(original_hex, 1, 0x12));
	return 0; 

}


unsigned replace_bytes(unsigned eight_bytes, int index, unsigned char replacement) {
	// throw err if index is outside of range for 4 byte number
	if (index >= 4){
		printf("Error:\t index %d is out of range\n", index);
		return 1;
	}

	unsigned new_bytes;

	if (index == 0){
		new_bytes = 0x000000FF & replacement;
	} else if (index == 1){
		new_bytes = 0x0000FF00 & replacement;
	} else if (index == 2){
		new_bytes = 0x00FF0000 & replacement;
	} else {
		new_bytes  = 0xFF000000 & replacement;
	}

	unsigned 
	return new_num;

