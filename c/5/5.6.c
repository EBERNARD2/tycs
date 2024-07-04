#include <stdio.h>
#include <ctype.h>

void reverse(char*);
int ato_i(char *);

int main(void)
{
  char s[] = "Reverse this string";
  reverse(s);
  printf("%s\n", s);

  char dig[] = "5478";

  printf("digit: %d\n", ato_i(dig));

  return 0;
}

int ato_i(char *s)
{
    int n = 0;

    while (isdigit(*s))
      n = 10 * n + (*s++ - '0');
    
    return n;
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