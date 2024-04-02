 #include <stdio.h>


typedef unsigned char *byte_pointer;

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

void test_show_bytes(int val){
    int ival = val;
    float fval = (float) val;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
    return;
}


 int main(void){

    //short x = 12345;

    // because this is a two's complement we need to add one to get the negative
    //short mx = ~x + 1;

    // Expansion of integers 
    short sx = -12345;
    unsigned short usx = sx; // should be 53191
    int x = sx; // -12345
    unsigned ux = usx;

    printf("sx = %d\t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    printf("usx =  %u\t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    printf("x = %d\t", x);
    show_bytes((byte_pointer) &x, sizeof(int));
    printf("ux = %d\t", ux);
    show_bytes((byte_pointer) &ux, sizeof(unsigned int));

    //show_bytes((byte_pointer) &x, sizeof(short));
    //show_bytes((byte_pointer) &mx, sizeof(short));

    return 0; 

 }