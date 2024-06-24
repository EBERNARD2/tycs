#include <stdio.h>

#define MAXLINE 2000 // Max size for line len

char line[MAXLINE];
int len;



void parser(void);
int get_line(void);

int main(void)
{
  extern int len;

  while((len = get_line()) > 0)
    ;
}


void parser(void)
{
  extern char line[];
  extern int len;
  char stack[MAXLINE];

  int i;

  
}


int get_line(void)
{
  extern char line[];
  extern int len;
  int i, c;

  for (i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  
  for (c = '\n')
    line[i++] = c;
  
  line[i] = '\0';

  return i;
}