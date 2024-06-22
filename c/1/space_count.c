#include <stdio.h>

int main(void)
{
  int blank_space, tabs, new_lines, c;

  blank_space = tabs = new_lines = 0;

  printf("Enter a sentence: ");
  
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      ++new_lines;

    if (c == '\t')
      ++tabs;
    
    if (c == ' ')
      ++blank_space;

    c = getchar();
  }

  printf("\n\n\nResults: \n\n\n Blank Spaces: %6d\n\n Tabs: %6d\n\n New Lines: %6d\n", blank_space, tabs, new_lines);

  return 0;
}