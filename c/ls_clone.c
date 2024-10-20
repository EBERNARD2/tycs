#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_PATH_LEN 100


int main(void)
{ 
  char *dirname = ".";

  char name[MAX_PATH_LEN];
  DIR *dir;
  struct dirent *ep;
  struct stat *st_buff;

  if ((dir = opendir(dirname)) == NULL) {
    fprintf(stderr, "can't open dir %s", dirname);
    return 1;
  }

  while ((ep = readdir(dir)) != NULL) {
    if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
      continue;
    if (strlen(dirname) + strlen(ep->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "name too long %s %s", dirname, ep->d_name);
      return 1;
    } else {
      stat(ep->d_name, st_buff);
      printf("%s - %llu\t", ep->d_name, st_buff->st_size);
    }

  }
}


