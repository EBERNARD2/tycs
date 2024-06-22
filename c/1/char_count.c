#include <stdio.h> 

int main(void) 
{
  double nc;

  nc = 0;

  for (nc = 0; getchar() != EOF; ++nc)
    ;

  printf("%.0f\n", nc);

  return 0;
}