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
int strcompn(char*, char* , int);
void treeprint(struct pnode *tree);
char *strdupl(char *s, int lim);



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

  if (tree == NULL) {
    tree = talloc();
    tree->count = 0;
    tree->pattern = strdupl(w, patternlen); // we want to set pattern if this is a new node
    tree->values[tree->count] = strdupl(w, strlen(w) + 1);
    tree->count++;
    tree ->left = tree -> right = NULL;
  } else if ((cond = strcompn(w, tree->pattern, patternlen))) {
    tree->values[tree->count] = strdupl(w, strlen(w) + 1);
    tree->count++;
  } else if (cond < 0) {
    tree->left = addtree(tree->left, w);
  } else 
    tree->right = addtree(tree->right, w);

  return tree;
}


int strcompn(char *s1, char *s2, int n)
{
  char *p = (char *) malloc(n);
  int i;

  for (i = 0; i < n; i++)
    *p++ = *s1++;
  
  *p = '\0';

  p -= n;

  i = strcmp(p, s2);

  free(p);

  return i;

}

// add string to values array of tree node
char *strdupl(char *s, int lim)
{
  int i = 0;
  char *p;
  p = (char *) malloc(lim + 1);

  if (p != NULL) 
    while(i < lim && (*p++ = *s++))
      i++;
  
  return p - (i + 1); //
}

 struct pnode *talloc(void)
 {
    return (struct pnode *) malloc(sizeof(struct pnode));
 }


void treeprint(struct pnode *tree)
{
  int i;
  if (tree != NULL) {
    treeprint(tree->left);
    // printf("Pattern %s\n", tree->pattern);
    for (i = 0; i < tree->count; i++)
      printf("%s\t\t", tree->values[i]); 
    printf("\n\n\n");
    treeprint(tree->right);
 }
}
