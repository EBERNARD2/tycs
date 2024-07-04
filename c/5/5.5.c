#include <stdio.h>


void strncpy(char *, char *, int);
void strncat(char *, char *, int);
void strncmp(char *, char *, int);

int main(void)
{
  return 0;
}

void strncpy(char *s, char *t, int n)
{
  int i = 0;
  while((*s++ = *t++) && i++ < n)
    ;
}

void strncat(char *s, char *t, int n)
{

  int i = 0; 
  while(*s)
    s++;

  do {
    if (i++ == n)
      return;
  } while((*s++ = *t++));
 
}

void strncmp(char * s, char * t, int n)
{
  int i;
  for (i = 0; *s++ == *t++ && i < n; i++)
    if (*s == '\0')
      return 0;

  return *s - *t;
}
