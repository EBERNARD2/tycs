#include <stdio.h>


/*

  Write the function strend(s,t), which returns 1 if the string t occurs at the
  end of the string s, and zero otherwise.

  Problem: 
    We want to return 1 if and only if t shows up at end of string s

    The end of the string s will be '\0'

    Basically, we want to iterate throguh s until we see s[i] == t[i]

    then once we found a match will iterate through the string until the values no longer match
    or we reach the end

    // if we are are the end of string s and t then we know we have a hit 

    if not then we end / continue 

*/


int strend(char *, char *);

int main(void)
{
  char t[] = "Trying this out";
  char s[] = "out";

  char n[] = "This won't work";
  char z[] = "won't ";

  printf("Example 1: %d\n", strend(t,s));
  printf("Example 2: %d\n", strend(n,z));

  return 0;
}


int strend(char *s, char* t)
{ 

  char *placeholder;

  while (*s) {

    if (*s == *t) {
      placeholder = t;
      while (*s++ == *t++ && *t != '\0')
        ;

      if (*s == '\0' && *t == '\0') /* We have a match at the end of a string*/
        return 0;
      
      t = placeholder; // reset pointer back to beginning of t
    }

    s++;
  }

  return -1;
}