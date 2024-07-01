#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);
int main(void)
{
  char s[100];
  itob(25, s, 2);
  printf("%s\n", s);
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
void itob(int n, char s[], int b)
{
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  i = 0;
  do {
    s[i++] = n % b + '0';
  } while ((n /= b) > 0);
  s[i] = '\0';
  reverse(s);
}
