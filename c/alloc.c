#include <stdio.h>
#define ALLOCSIZE 10000

static char allocbuff[ALLOCSIZE]; // the address of the star of the array
static char *allocp = allocbuff;
/// array adress 0x1234 + 0x3E8 (1000) - the current allocate pointer
char *alloc(int n) {
    if (allocbuff + ALLOCSIZE - allocp >= n) {
      allocp += n;
      return allocp - n;
    } else {
      return 0;
    }
}

void afree(char *p) {
  // if we've already used space AND we still have space left 
  if (p >= allocbuff && p < allocbuff + ALLOCSIZE)
    allocp = p;
}