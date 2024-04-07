#include <stdio.h>

unsigned replace_bytes(unsigned four_bytes, int index, unsigned char replacement);

int main(void){

	int original_hex = 0x12345678;

	printf("replace bytes %X\n", replace_bytes(original_hex, 3, 0x12));
	return 0; 

}


unsigned replace_bytes(unsigned four_bytes, int index, unsigned char replacement) {
	// throw err if index is outside of range for 4 byte number
	if (index >= 4){
		printf("Error:\t index %d is out of range\n", index);
		return 1;
	}
	int byte_to_update = 3 - index;

	unsigned new_bytes;

	// create new set of bytes based -> remove byte based on index -> add replacement 
	// (shited to right place) with or bitwise operator
	if (index == 0){
		unsigned insert_byte = 0xFFFFFF00 & four_bytes;
		new_bytes = insert_byte | replacement;
	} else if (index == 1){
		unsigned insert_byte = 0xFFFF00FF & four_bytes;
		unsigned byte_to_replace = replacement;
		byte_to_replace <<= 8;
		new_bytes = insert_byte | byte_to_replace;
	} else if (index == 2){
		unsigned insert_byte = 0xFF00FFFF & four_bytes;
		unsigned byte_to_replace = replacement;
		byte_to_replace <<= 16;
		new_bytes = insert_byte | byte_to_replace;
	} else if (index == 3){
		unsigned insert_byte = 0x00FFFFFF & four_bytes;
		unsigned byte_to_replace = replacement;
		byte_to_replace <<= 24;
		new_bytes = insert_byte | byte_to_replace;
	}

	return new_bytes;
}
