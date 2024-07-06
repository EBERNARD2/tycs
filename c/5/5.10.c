#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100 /* Stack max */
#define NUMBER '0'
static int stack[MAX];
static int sp = 0;


void push(int n);
int pop(void);
int gettype(char *);

int main(int argc, char *argv[])
{
  int type, op2;
  if (argc == 1)
    printf("Usage: expr (polish expression)\n");
  else {
    while (*++argv) {
      int type = gettype(*argv);

      switch (type) {
        case NUMBER:
          push(atoi(*argv));
          break;
        case '+':
          push(pop() + pop());
          break;
        case '-':
          op2 = pop();
          push(pop() - op2);
          break;
        case '*':
          push(pop() * pop());
          break;
        case '/':
          op2 = pop();
          push(pop() / op2);
          break;
        case '%':
          op2 = pop();
          push(pop() % op2);
          break;
        default:
          printf("error: unknown command %s\n", *argv);
          break;
       }
    }

    printf("Result: %d\n", stack[0]);
  }

  return 0;
}


int gettype(char *arg)
{
  if (!atoi(arg) && *arg != '0')
    return *arg;
  else
    return NUMBER;

}

int pop(void)
{
  if (sp > 0)
    return stack[--sp];
  else {
    printf("error: stack empty\n");
    return 0;
  }
}


void push(int n)
{
  if (sp < MAX)
    stack[sp++] = n;
  else
    printf("Error: stack full, cannot push %d\n", n);
}