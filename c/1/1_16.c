#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int lim);


int main(void)
{
  int len, i;

  char line[MAXLINE];
  
  while((len = get_line(line, MAXLINE)) > 0) {
    i = 0; 
    while (i < len)
      printf("%c", line[i++]);
    printf("\n\n");
  }

  return 0;
}

int get_line(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) 
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  
  s[i] = '\0';

  return i;
} 
