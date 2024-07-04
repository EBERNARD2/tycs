#include <stdio.h>
#include <ctype.h>


#define SIZE 100
#define BUFFSIZE 100


int getch(void);
void ungetch(int);
int getint(int *);


char buf[BUFFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main(void)
{
  int n, array[SIZE];
  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    ;

  return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
  int c, sign;
  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  
  if (!isdigit((c =getch()))) {
    ungetch(c);
    ungetch(sign ? '+' : '-');
    return 0;
  }

  for (*pn = 0; isdigit(c), c = getch();)
    *pn = 10 * *pn + (c - '0');
    *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int getch(void) /* get a (possibly pushed-back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
