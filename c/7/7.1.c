#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[])
{
  int c; 

  printf("testing %d\n",  strcmp(argv[0], "upper"));
  if (strcmp(argv[0], "lower")  == 0 || strcmp(argv[0], "Lower")  == 0 )
    while ((c = getchar()) != EOF)
      putchar(tolower(c));
  else if (strcmp(argv[0], "Upper")  == 0  || strcmp(argv[0], "upper")  == 0 )
    while ((c = getchar()) != EOF)
      putchar(toupper(c));
  else 
    printf("%s\n", argv[0]);

  return 0;
}