#include <stdio.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len);
void show_int(int x);
void show_float(float x);
void show_pointer(void *x);
void test_show_bytes(int val);
void show_double(double x);
void show_long(long x);



int main(void){

	float y = 3.12450495883;
	double x = y;
	long test = 2178309059684;

	show_int(1);
	show_double(x);
	show_float(y);
	show_long(test);

	return 0;
}

 void show_bytes(byte_pointer start, size_t len){
    int i = 0;

    for (i=0; i < len; i++){
        printf("%.2x ", start[i]);
    }

    printf("\n");
    return; 
 }

void show_int(int x){
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_double(double x){
	show_bytes((byte_pointer) &x, sizeof(double));
}

void show_long(long x){
	show_bytes((byte_pointer) &x, sizeof(long));
}