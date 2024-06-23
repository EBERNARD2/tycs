#include <stdio.h>

#define TAB_LEN 5
#define MAXLINE 1000

char line[MAXLINE];
int len;

int get_line(void);
void detab(void);



int main(void)
{

  extern char line[];
  extern int len;

  while((len = get_line()) > 0) {
    detab();
  }

  return 0;
}


void detab(void)
{
  int counter, i, j;
  extern char line[];
  extern int len;

  for (i = 0; i < len; i++) {
    // check if value is a tab
    if (line[i] == '\t') {
      counter = TAB_LEN - (i % TAB_LEN);

      for (j = 0; j < counter; j++)
        printf(" ");
    } else 
      printf("%c", line[i]);
  }

  printf("\n\n");

}

int get_line(void)
{
  int i, c;
  extern char line[];

  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  
  if (c == '\n')
    line[i++] = c;
  
  line[i]  = '\0';

  return i;
}

