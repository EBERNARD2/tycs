#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// get directory contents 
#define MAX_PATH_LEN 1024

void dirwalk(char *, void (*fn) (char*));
void printfile(char *);

// print directory contents
int main(int argc, char *argv[])
{

  DIR *dir;
  struct dirent *ep;
  struct stat *st_buff;


  if (argc == 1)
    printfile(".");
  else 
    printfile(*++argv);
  printf("\n");

  return 0;
}




void dirwalk(char *dirname, void (*fn) (char*)) 
{
  char name[MAX_PATH_LEN];
  DIR *dir;
  struct dirent *ep;

  if ((dir = opendir(dirname)) == NULL) {
    fprintf(stderr, "dirwalk: can't open dir %s", dirname);
    return;
  }

  while ((ep = readdir(dir)) != NULL) {
    if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
      continue;
    if (strlen(dirname) + strlen(ep->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwalk: name too long %s %s", dirname, ep->d_name);
      return;
    } else 
      (*fn)(ep->d_name);
  }

}

void printfile(char *filename)
{
  struct stat *st_buff;

  if (stat(filename, st_buff) == -1)
    fprintf(stderr, "printfile: can't access file: %s", filename);
    return;


  if ((st_buff->st_mode & S_IFMT) == S_IFDIR)
    dirwalk(filename, printfile);

  printf("%s - %llu\t", filename, st_buff->st_size);
}

