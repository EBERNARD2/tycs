#include <stdio.h>


#define MAXLINE 1000

char s[MAXLINE];
int len;

void escape(void);

int main(void)
{
  while(get_text() > 0)
    escape();
    
  return 0;
}

int get_text(void)
{
  extern int len;
  extern char s[];

  int c;

  for(len = 0; (c = getchar()) != EOF && len < MAXLINE - 1; len++)
    s[len++] = c;
  
  s[len] == '\0';

  return len;

}

void escape(void)
{
  char t[MAXLINE];
  extern char s[];
  extern int len;
  int i, c;

  i = 0;
  
  while(i < len - 1) {
    c = s[i];
    switch(c) {
      case '\n':
        t[i] = "newline";
        break;
      case '\t':
        t[i] = 'tab';
        break;
      default:
        t[i] = c;
        break;
    }
  }
}
