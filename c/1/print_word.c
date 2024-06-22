#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
  int c, nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;

  printf("\n");

  while((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n')
      ++nl;

    if (c == ' ' || c == '\t' || c == '\n') {
      printf("\n");
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      ++nw;
    }

    if (state == IN)
      putchar(c);
  }

  return 0;
}