#include <stdio.h>
#include <stdlib.h> /* for atof() */


#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
int bufp = 0;

char buf[BUFSIZE]; 
double val[MAXVAL];



int getop(char []);
void push(double);
double pop(void);
int getchr(void);
void ungetchr(int c);


/* reverse Polish calculator */

int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor");
        break;
        case '\n':
          printf("\t%.8g\n", pop());
          break;
        default:
          printf("error: unkown command %s\n", s);
          break;
      }
  }

  return 0;
}


void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else 
    printf("error: stack full, can't push %g\n", f);

}

double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
    printf("error: stack empty\n");
    return 0.0;
}

int getchr(void)
{
  return  (bufp > 0) ? buf[--bufp] : getchar();
}