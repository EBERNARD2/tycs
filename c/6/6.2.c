#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXVALUES 100
#define DEFAULT_PATTERN_LEN 6
#define MAXWORD 100
#define BUFFSIZE 100

int patternlen = DEFAULT_PATTERN_LEN;
char buff[BUFFSIZE];
int bufp = 0;

bool isvalidnum(char *);
int getword(char *, int);
int getch(void);
void ungetch(int c);

struct pnode {
  char *pattern; // This variable (and left + right nodes) will be used to create a binary search tree of all patterns in Lexicographic order
  char *values[MAXVALUES]; // Each string value that meets that pattern
  int count; // Count of values in array
  struct pnode *left;
  struct pnode *right;
};


int main(int argc, char *argv[])
{

  char word[MAXWORD];
  if (argc > 1 && isvalidnum(*++argv))
    patternlen = atoi(*argv);

  struct pnode *root;

  root = NULL;

  // get next value from input 
  while (getword(word, MAXWORD) != EOF)
    // if value is a word and it's length is greater than or eql to patternlen add it to BST

  
  // print BST
  return 0;
}


bool isvalidnum(char *s)
{
  if (s[0] == '-')
    return false;
  for (; *s != '\0'; s++)
    if (!isdigit(*s))
      return false;
  return true;
}


 /* getword: get next word or character from input */
 int getword(char *word, int lim)
 {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
    
  *w = '\0';
  return word[0];
 }
 

 int getch(void) /* get a (possibly pushed-back) character */
 {
  return (bufp > 0) ? buff[--bufp] : getchar();
 }

 void ungetch(int c) /* push character back on input */
 {
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else
    buff[bufp++] = c;
 }
