#include <stdio.h>
#include <string.h>

void str_cat(char *s, char *t);

int main(void) 
{

  char *s = "hello";

  printf("Before: %c\n", *s);
  char *t = "world";

  str_cat(s, t);

  printf("\"%s\"\n", s);

  return 0;
}


void str_cat(char *s, char *t)
{
  while (*s) /* find end of s */
	  ++s;
  while ((*s++ = *t++)) /* copy t */
    ;
}