#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000

int get_line(char l[], int max);
bool blank_line(char l[], int len);
void remove_trailing_spaces(char src[], int len);



int main(void)
{
  char line[MAXLINE];
  int len, i;

  while((len = get_line(line, MAXLINE)) > 0) {
    if (blank_line(line, len))
      continue;
    for (i = 0; i < len; i++)
      printf("%c", line[i]);

    printf("\n");
  }
  
}

bool blank_line(char l[], int len)
{
  int i = 0;



  while (i < len)
  {
    if (l[i] - '0' > 32)
      return false; 
    i++;
  }

  return true;

}


int get_line(char dest[], int lim)
{

  int i, c;
  bool continuos_spaces = false;

  for (i = 0; (c = getchar()) != EOF && c != '\n' && i < lim- 1; i++) {
    if (c - '0' < 33 && !continuos_spaces)
      continuos_spaces = true;
    else if (c - '0' > 33)
      continuos_spaces = false;
    else if (continuos_spaces)
      continue;

    dest[i] = c;
  }

  if (c == '\n') 
    dest[i++] = c;
  
  dest[i] = '\0';

  return i; 
  
}