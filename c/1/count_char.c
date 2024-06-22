#include <stdio.h>

#define LENGTH 256

int main(void)
{
  int chars[LENGTH] = {0}; // Save a slot for all LENGTH chars
  int c, i; 

  while ((c = getchar()) != EOF) {
    chars[c - '0']++;
  }


  printf("Character Count from input stream: \n\n");

  for (i = 0; i < LENGTH; i++) {
    if (chars[i]){
      printf("%c\t\t", i + '0');
      for (int count = chars[i]; count > 0; count--)
        printf("X");
      printf("\t\t\t\t %c appeared  %d time(s)\n", i + '0', chars[i]);
    }
  }


  return 0;

}