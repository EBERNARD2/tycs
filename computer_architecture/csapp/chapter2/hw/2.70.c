#include <stdio.h>
#include <assert.h>

int fit_bits(int x, int n);

int main(void){
    assert(fit_bits(0xffffffff, 10) == 0);
    assert(fit_bits(26, 5) == 1);
    return 0;
}

int fit_bits(int x, int n){
    int shifted_n = 1 << (n-1);
    int mask = shifted_n |= shifted_n -1;

    int cmp = x & shifted_n;

    return x == cmp;
}