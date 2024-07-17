#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmts, ...);

int main(void)
{
  int i;
  float f;
  char c;
  char *st;

  printf("Enter int: ");
  minscanf("%d", &i);
  printf("Check int is correct: %d \n", i);
  printf("Enter floating point num: ");
  minscanf("%f", &f);
  printf("Check float is correct: %f\n", f);

  printf("Enter string: ");
  minscanf("%s", &st);
  printf("Check string is correct: %s\n", st);

  printf("Enter a single char: ");
  minscanf("%c", &c);
  printf("Check char is correct: %d \n", i);

  printf("Enter an int, then a string, then a float: ");
  minscanf("%d %s %f", &i, &st, &f);
  printf("Check inputs are correct: %d, %s, %f\n", i, st, f);


  return 0;
}

void minscanf(char *fmts, ...)
{
  va_list ap;
  char *p, *sval;
  int *ip; 
  double *dp;
  
  va_start(ap, fmts);

  for (p = fmts; *p; p++) {
    if (*p != '%')
      continue;
    switch (*++p) {
      case 'd':
        ip = va_arg(ap, int*);
        scanf("%d", ip);
        break;
      case 'f':
        dp = va_arg(ap, double*);
        scanf("%f", dp);
        break;
      case 'c':
        ip = va_arg(ap, int*);
        scanf("%d", ip);
        break;
      case 's':
        sval = va_arg(ap, char*);
        printf("%x", sval);
        scanf("%s", sval);
        break;
    }
  }
}