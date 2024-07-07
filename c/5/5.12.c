#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define DEFAULT_TAB_SIZE 5
#define DEFAULT_START_COL 5
#define IN 1
#define OUT 1

int len;
char current_line[MAXLINE];

int tab_size = DEFAULT_TAB_SIZE;
int starting_col = DEFAULT_START_COL;

void entab(void);
int get_line(void);
int get_blank_end_index(int start);
void detab(void);


// entab -m +n tab stops every n columns starting at m
int main(int argc, char *argv[])
{
  extern int len;
  extern int tab_size;
  extern int starting_col;

  // process command line arguments
  if (argc > 1) {
    while (*++argv) {
      if (*argv[0] == '-') {

        starting_col = -1 * atoi(argv[0]);
      }

      if (*argv[0] == '+')
        tab_size = atoi(argv[0]);
    } 
  } 


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
  extern int tab_size;
  extern int starting_col;
  int i, j, total_spaces, tabs, blanks;

  for (i = 0; i < len - 1; i++) {
    if (current_line[i] - '0' == 32 && i >= starting_col) {
      j = get_blank_end_index(i);

      total_spaces = j - i + 1;

      tabs = total_spaces / tab_size;
       
      blanks = total_spaces % tab_size;

      for (int t = 0; i < tabs * tab_size; t++)
        printf("\t");

      for (int k = 0; k < blanks; k++)
        printf(" ");
      
      i = j + 1;
      
    } else
      printf("%c", current_line[i]);
      
  }

  printf("\n");

}

void detab(void)
{
  int counter, i, j;
  extern char current_line[];
  extern int len;

  for (i = 0; i < len; i++) {
    // check if value is a tab
    if (current_line[i] == '\t') {
      counter = DEFAULT_TAB_SIZE - (i % DEFAULT_TAB_SIZE);

      for (j = 0; j < counter; j++)
        printf(" ");
    } else 
      printf("%c", current_line[i]);
  }

  printf("\n\n");

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