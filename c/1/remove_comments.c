#include <stdio.h>
#include <stdbool.h>


#define MAXLINE 1000
#define IN 1
#define OUT 0


char current_line[MAXLINE];
int len;


int get_line(void);
void remove_comments(void);

int main(void)
{
  extern char current_line[];
  extern int len;

  while((len = get_line()) > 0)
    remove_comments();

  return 0;

}


int get_line(void)
{
  extern char current_line[];

  int i, c;

  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    current_line[i] = c;

  if (c == '\n')
    current_line[i++] = c;

  current_line[i] = '\0';
  return i;

}

void remove_comments(void)
{
  extern char current_line[];
  extern int len;

  bool single_comment_state, multi_comment_state;
  single_comment_state = multi_comment_state = OUT;

  int i;

  /*
    We have a few scenarios:

    at the start of each type of comment, we turn on that state 

    so if it is a single comment and new line, the single comment should end thus releasing the single comment state

    if we are in a multi line comment, we continue to iterate until we see the closing tags then release multi comment state


    if those states are on, we continue iterating
    otherwise we print out the character 

  */

  for (i = 0; i < len - 1; i++){
    // Two comments... single comment and multiline comments
    bool s_comment_start = current_line[i] == '/' && current_line[i + 1] == '/';
    bool m_comment_start = current_line[i] == '/' && current_line[i + 1] == '*';


    if (s_comment_start)
      single_comment_state = IN;
    
    if (m_comment_start)
      multi_comment_state = IN;
    

    if (single_comment_state && current_line[i] == '\n') {
      single_comment_state = OUT;
      continue;
    }

    if (multi_comment_state && current_line[i] == '*' && current_line[i + 1] == '/' ) {
      multi_comment_state = OUT;
      continue;
    }

    bool write_out = !(single_comment_state || multi_comment_state);

    if (write_out)
      printf("%c", current_line[i]);

  }
}