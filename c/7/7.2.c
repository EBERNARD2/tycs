#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(void)
{

  char c = 'a';
  minprintf("This will be a test %x\n", 123);
  minprintf("Test without values\n");
  minprintf("Longer test %d, %c, %f\n", 150, c, 1.4);

  return 0;
}


void minprintf(char *fmt, ...)
{
  va_list ap;
  char *p, *sval;
  int ival;
  unsigned int uval;
  double dval;
  va_start(ap, fmt); /* make ap point to 1st unnamed arg */

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
      case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    case 'c':
      ival = va_arg(ap, int);
      putchar(ival);
      break;
    case 'x':
      ival = va_arg(ap, int);
      printf("%x", ival);
      break;
    case 'u':
      uval = va_arg(ap, unsigned int);
      printf("%u", uval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}
