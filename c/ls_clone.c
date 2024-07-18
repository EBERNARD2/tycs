#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
  DIR *dp;
  struct dirent *ep;

  dp = opendir(".");

  if (dp == NULL) {
    fprintf(stderr, "Directory does not exist:\n");
    exit(1);
  }

  if (dp != NULL) {
    while ((ep = readdir(dp)) ) {
      printf("%s\t", ep->d_name);
      (void) closedir (dp);
    }
  }
  int i = 0;
  for (; i < 100; i++)
    printf("23\t");
  return 0;
}