#include <stdio.h>
#include "syscalls.h"
/* cat: concatenate files, version 1 */

  /* filecopy: copy file ifp to file ofp */

int main(int argc, char *argv[])
{
  FILE *fp;
  void filecopy(FILE *, FILE *);
  if (argc == 1)
    filecopy(stdin, stdout);
  else
    while(--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) { // read here 
        printf("cat: can't open %s\n", *argv); // error here
        return 1;
      }
      else {
        filecopy(fp, stdout);
        fclose(fp);
      }

  return 0;
}

void fileCopy(FILE *ifp, FILE *ofp)
{
  int c;
  while ((c = getc(ifp)) != EOF) // read here 
    putc(c, ofp); /// write here
}