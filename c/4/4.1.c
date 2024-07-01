#include <stdio.h>


int strindex(char s[], char t[]);

char pattern[] = "ould";

int main(void)
{

  char s[] = "wofld cfb shovdld";
  printf("%d\n", strindex(s, pattern));
  return 0;
}

int strindex(char s[], char t[])
{
  int i, j, k, found;

  found = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    
    if (k > 0 && t[k] == '\0')
      found = i;
  }

  return found;
}