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


int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

struct wordnode {
  char *word;
  int count;
  struct wordnode *left;
  struct wordnode *right;
};


// Need a function to build tree and update values - recursive 
struct wordnode *addtree(struct wordnode *, char *);
struct wordnode *talloc(void);
char *dupl(char *);

// need a function to add word nodes (with count) to array 
int buildarray(struct wordnode *, struct wordnode *);
// need a function to sort in order 
struct wordnode *wordnodesort(struct wordnode *[], int, int);
// Finally need a function to print all of these values 
void printvalues(struct wordnode *, int);


int main(int argc, char *argv[])
{

  char word[MAXWORD];
  struct wordnode *allwords[MAX_UNIQ_WORDS];
  int len;

  struct wordnode *root;

  root = NULL;

  while((getword(word, MAXWORD)) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);

  if (root != NULL)
    len = buildarray(allwords, root);

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


struct wordnode *addtree(struct wordnode *tree, char *word)
{
  int cond;

  if (tree == NULL) {
    tree = talloc();
    tree->word = dupl(word);
    tree->count = 1;
    tree->left = tree->right = NULL;
  } else if ((cond = strcmp(word, tree->word)) == 0) {
    tree->count++;
  } else if (cond < 0) {
    tree->left = addtree(tree->left, word);
  } else 
    tree->right = addtree(tree->right, word);

  return tree;
}


struct wordnode *talloc(void)
{
  return (struct wordnode *) malloc(sizeof(struct wordnode));
}

char *dupl(char *s) {
  char *p;

  p = (char *) malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}


int buildarray(struct wordnode *dest, struct wordnode *tree)
{
  int i; 

  struct wordnode *p = tree;

  while(p) {

  }
}

