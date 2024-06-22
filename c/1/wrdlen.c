#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
  int current_word[100];
  int state, c, letter_count, i, j;

  state = OUT;
  i = j = 0;

  while ((c = getchar()) != EOF) {
    // when we encounter empty space then the word is done
    if ((c == '\t' || c == '\n' || c == ' ') && letter_count > 0 && state == IN) {
      state = OUT;
      j = 0;
      printf("\n\n");

      while (j < i) 
        putchar(current_word[j++]);

      printf("\t\t");
      
      // when we exit a word print it's data
      for (j = 0; j < letter_count; j++)
        printf("X\t");

      printf("\n");

    } else if (state == OUT && (c != '\t' || c != '\n' || c != ' ')) {
      i = 0;
      current_word[i++] = c;
      letter_count = 1;
      state = IN;

    } else if (state == IN) {
      current_word[i++] = c;
      letter_count++;
    }

  }

  return 0;
}