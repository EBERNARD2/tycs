#include <stdio.h>

#define MAXLINE 1000
#define N 50


char line[MAXLINE];
int len;


int get_line(void);
void print_sub_lines(void);


int main(void)
{
  extern char line[];
  extern int len;

  while((len = get_line()) > 0)
    print_sub_lines();
}

void print_sub_lines(void)
{ 
  extern char line[];
  extern int len;

  int i, j; 

  printf("\n");

  for (i = 0; i < len - 1; i++) {
    if (j == N) {
      printf("\n%c", line[i]);
      j = 0;
    } else {
      printf("%c", line[i]);
      ++j;
    }
  }

}


int get_line(void)
{
  extern char line[MAXLINE];

  int i, c;
  
  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;

  if (c == '\n')
    line[i++] = c;
  
  line[i] = '\0';

  return i;

}



