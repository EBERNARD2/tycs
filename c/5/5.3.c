#include <stdio.h>

void stringcat(char *, char *);


int main(void)
{

  char test[100] = "this is ";
  char test2[] = "not a drill.";

  stringcat(test, test2);
  printf("%s\n", test); 
  return 0;
}


void stringcat(char * s, char * t)
{

  while(*s)
    s++;

  while((*s++ = *t++))
    ;
  
}