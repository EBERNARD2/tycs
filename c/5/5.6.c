#include <stdio.h>

void reverse(char*);

int main(void)
{
  char s[] = "Reverse this string";

  reverse(s);

  printf("%s\n", s);
  return 0;
}

void reverse(char* s)
{
  int temp;
  char *e = s;

  while (*e)
    e++;

  --e;

  while(s != e) {
    temp = *s;
    *s = *e;
    *e = temp;
    s++;
    e--;
  }

}