#include <stdio.h>

#define MAXLINE 1000

int get_line(char dest[], int max);


int main(void)
{
  char current_line[MAXLINE]; 
  int len, i;

  while((len = get_line(current_line, MAXLINE)) > 0) {
      if (len > 80) {
        i = 0;

        while(i < len)
          printf("%c", current_line[i++]);
      }
      printf("\n\n");
  }
  
  return 0;
}

int get_line(char dest[], int lim)
{
  int i, c;

  for (i = 0; (c = getchar()) != EOF && c != '\n' && i < MAXLINE - 1; i++)
    dest[i] = c;

  if (c == '\n') 
    dest[i++] = c;
  
  dest[i] = '\0';

  return i; 
}