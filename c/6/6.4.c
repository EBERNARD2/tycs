#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAXWORD 100
#define MAX_UNIQ_WORDS 10000

#define BUFFSIZE 100

char buff[BUFFSIZE];
int bufp = 0;
int line = 0;
/*
  Need to find a structure that can:
    - Store word 
    - store times word appared in input stream 
    - we don't want this in a tree structure as it would be hell to print it 
    - Maybe not actually.. 
    - We still need to sort values so we can find the word that we want to update the count
    - after traversing document, we would put nodes into 

*/

int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

struct wordnode {
  char *word;
  int count;
};


struct wordnode *words[MAX_UNIQ_WORDS];



int main(int argc, char *argv[])
{

  char word[MAXWORD];

  while((getword(word, MAXWORD)) != EOF)
    if (isalpha(word[0]))
      ;


}

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
