#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



bool ispangram(char *s) {
  // TODO implement this!
  char t = *s;
  // iterate through entire line
  printf("%c", tolower(t));
  
  // keep track of 
  // 

  return false;
}

int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (ispangram(line))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
}
