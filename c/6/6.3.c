#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 100
#define BUFFSIZE 100
#define MAXWORD 100

char buff[BUFFSIZE];
char temp[MAXWORD];
int bufp = 0;
int line = 0;

int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
char *strdupl(char *s);
struct wordnode *talloc(void);
struct wordnode *addword(struct wordnode *, char *s);
void printwtree(struct wordnode *);

struct wordnode {
  char *word;
  int current_capacity;
  int lines[MAXLINES];
  struct wordnode *left;
  struct wordnode *right;
};

int main(int argc, char *argv[])
{

  char word[MAXWORD];
  struct wordnode *root;

  root = NULL;

  while(getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
       root = addword(root, word);

  printf("\n\n");

  printwtree(root);
  return 0;
}

int validword(char *word)
{
  return 1;
}

struct wordnode *addword(struct wordnode *wtree, char *w)
{
  int cond;

  if (wtree == NULL) {
    wtree = talloc();
    wtree->word = strdupl(w);
    wtree->current_capacity = 0;
    wtree->lines[wtree->current_capacity++] = line;
    wtree->left = wtree->right =NULL;
  } else if ((cond = strcmp(w, wtree->word)) == 0) {
    wtree->lines[wtree->current_capacity++] = line;
  } else if (cond < 0)
    wtree->left = addword(wtree->left, w);
  else 
    wtree->right = addword(wtree->right, w);

  return wtree;
}


/* getword: get next word or character from input */
 int getword(char *word, int lim)
 {

  int c, getch(void);
  void ungetch(int);
  char *w = word;

  if ((c = getch()) == '\n') {
    line++;
    return c;
  }

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
      if (*w == '\n')
        line++;
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


char *strdupl(char *s)
{
  int i = 0;
  char *p;
  p = (char *) malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

 struct wordnode *talloc(void)
 {
    return (struct wordnode *) malloc(sizeof(struct wordnode));
 }


 void printwtree(struct wordnode *tree)
 {
    int i;

    if (tree != NULL) {
      printwtree(tree->left);
      printf("Word: %s\n", tree->word);
      printf("Lines found:\t");
      for (i = 0; i < tree->current_capacity; i++)
        printf("\t%d ", tree->lines[i]);
      printf("\n");
      printwtree(tree->right);

    }
 }

