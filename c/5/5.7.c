#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
char *alloc(int);

int readlines(char *lineptr[], int nlines);
void writelines(char *linepter[], int nlines);
void qsort(char * lineptr[], int left, int right);

int main(void)
{

  char *lines[MAXLINES];
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}


int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];
  nlines = 0;
  
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines)
      return -1;
    else {
      line[len-1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }

  return nlines;
}


void writelines(char *lineptr[], int nlines)
{
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}
