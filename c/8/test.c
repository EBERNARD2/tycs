#include <stdio.h>

int main(void) {
  int c;

  c = getchar();

  while(c != '\0') {
    putchar(c);
    c = getchar();
  }

  

  return 0;
}