#include <stdio.h>
#include <string.h>

void i_to_a(int n, char s[], int min_width);
void reverse(char s[]);

int main(void)
{
  char s[1000];
  i_to_a(20, s, 70);
  printf("%s\n", s);
  return 0;
  
}


void reverse(char s[])
{
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void i_to_a(int n, char s[], int min_width)
{
  int i, sign;

  if ((sign = n) < 0)
    n = -n;
  i = 0;  
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  
  for (; i < min_width; i++)
    s[i] = ' ';

  reverse(s);
}
