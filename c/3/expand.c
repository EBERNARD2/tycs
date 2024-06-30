#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main(void)
{

  char s[] = "-a-z0-9";
  char dest[MAXLINE];

  return 0;
}


/*
  Assumptions:
  
  lowercases will be matched with lowercases

  uppercases will be matched with uppercases

  digits will be matched with digits

  valid representations: 

    a-b-m0-9

    -a-v0-9-

    0-8-r-z


invalid representations:

A-b

0-r
2-C
m-A




*/
void expand(char s1[], char s2[])
{

}