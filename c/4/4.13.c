#include <stdio.h>
#include <string.h>

void reverse_str(char s[], int i, int j);

int main(void)
{

  char s[] = "hello my name is";
  int len = strlen(s);
  reverse_str(s, 0, len - 1);
  printf("%s\n", s);
  return 0;
}

void reverse_str(char s[], int i, int j)
{
  if (i >= j)
    return;

  int c = s[i];

  s[i] = s[j];
  s[j] = c;

  reverse_str(s, ++i, --j);
}