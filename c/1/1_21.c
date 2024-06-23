#include <stdio.h>

#define MAXLINE 1000
#define TAB_SIZE 5
#define IN 1
#define OUT 1

int len;
char current_line[MAXLINE];


void entab(void);
int get_line(void);
int get_blank_end_index(int start);

int main(void)
{
  extern int len;


  while ((len = get_line()) > 0)
    entab();

  return 0;
}


int get_blank_end_index(int blank_start)
{
  extern char current_line[];
  extern int len;

  int i;

  i = ++blank_start;

  while(current_line[i++] - '0' == 32 && i < len - 1)
    ;
  
  return i;
}


void entab(void)
{

  extern char current_line[];
  extern int len;
  int i, j, total_spaces, tabs, blanks;

  for (i = 0; i < len - 1; i++) {
    if (current_line[i] - '0' == 32) {
      j = get_blank_end_index(i);

      total_spaces = j - i + 1;

      tabs = total_spaces / TAB_SIZE;
       
      blanks = total_spaces % TAB_SIZE;

      for (int t = 0; i < tabs * TAB_SIZE; t++)
        printf("\t");

      for (int k = 0; k < blanks; k++)
        printf(" ");
      
      i = j + 1;
      
    } else
      printf("%c", current_line[i]);
      
  }

  printf("\n");

}

int get_line(void)
{
  int i, c;
  extern char current_line[];
  extern int len;

  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    current_line[i] = c;

  if (c == '\n')
    current_line[i++] = c;

  current_line[i] = '\0';

  return i;
}