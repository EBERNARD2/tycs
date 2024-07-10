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
char temp[MAXWORD];
int bufp = 0;

struct pnode {
  char *pattern; // This variable (and left + right nodes) will be used to create a binary search tree of all patterns in Lexicographic order
  char *values[MAXVALUES]; // Array of pointers to string value that meets that pattern
  int count; // Count of values in array
  struct pnode *left;
  struct pnode *right;
};


bool isvalidnum(char *);
int getword(char *, int);
int getch(void);
void ungetch(int c);
struct pnode *addtree(struct pnode *, char *);
struct pnode *talloc(void);
void treeprint(struct pnode *tree);
char *strdupl(char *s);
void copynchars(char *s);



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
    if (isalpha(word[0]) && strlen(word) >= patternlen)
      root = addtree(root, word);

  // print BST
  treeprint(root);
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

void copynchars(char *s)
{
  int i; 
  
  for (i = 0; i < patternlen; i++) 
    temp[i] = *s++;
  
  temp[i] = '\0';
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


 struct pnode *addtree(struct pnode *tree, char *w)
 {
  int cond;

  copynchars(w);

  if (tree == NULL) {
    tree = talloc();
    tree->count = 0;
    tree->pattern = strdupl(temp); // we want to set pattern if this is a new node
    tree->values[tree->count] = strdupl(w);
    tree->count++;
    tree ->left = tree -> right = NULL;
  } else if ((cond = strcmp(temp, tree->pattern)) == 0) {
    tree->values[tree->count] = strdupl(w);
    tree->count++;
  } else if (cond < 0) {
    tree->left = addtree(tree->left, w);
  } else 
    tree->right = addtree(tree->right, w);

  return tree;
}


// add string to values array of tree node
char *strdupl(char *s)
{
  int i = 0;
  char *p;
  p = (char *) malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

 struct pnode *talloc(void)
 {
    return (struct pnode *) malloc(sizeof(struct pnode));
 }


void treeprint(struct pnode *tree)
{
  printf("\n\n");

  int i;
  if (tree != NULL) {
    treeprint(tree->left);
    printf("Pattern\n");
    char *p = tree->pattern;
    for (i = 0; i < tree->count; i++)
      printf("%s\n", tree->values[i]); 
    printf("\n\n\n");
    treeprint(tree->right);
 }
}
