#include <stdio.h>

#define MAXLINE 1000

int get_line(char dest[], int lim);
void reverse_str(char src[], int len);

int main(void)
{
  char line[MAXLINE];

  int len;

  while((len = get_line(line, MAXLINE)) > 0) {
    reverse_str(line, len);
  }

  return 0;
}


void reverse_str(char src[], int len)
{
  int i;

  for (i = len - 1; i >= 0; i--)
    printf("%c", src[i]);
  
  printf("\n");
}



int get_line(char dest[], int lim)
{
  int c, i; 

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    dest[i] = c;
  
  if (c == '\n')
    dest[i++] = c;

  dest[i] = '0';

  return i;
}