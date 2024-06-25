#include <stdio.h>


#define LIMIT 1000
// i < lim-1 && (c=getchar()) != '\n' && c != EOF

// we could use conditional logic in variables that we update

// could change this to a while loop 
int main(void)
{

  int c, i;

  i = 0;

  while(i < LIMIT - 1) {
    
    if ((c = getchar()) == '\n')
      break;
    
    if (c == EOF)
      break;
  }

  return 0; 
}