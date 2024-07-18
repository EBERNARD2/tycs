#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_SIZE 10000

struct {
  char *name;
  int filesize;
} DIR_CONTENTS[MAX_SIZE];

// get directory contents 

// print directory contents
int main(void)
{
  DIR *dir;
  struct dirent *ep;

  dir = opendir(".");

  if (ep == NULL) {
    fprintf(stderr, "Directory does not exist:\n");
    exit(1);
  }

  while ((ep = readdir(dir)) != NULL) 
    printf("%s\t", ep->d_name);

  printf("%ld\n", dir->__dd_size);  
  return 0;
}