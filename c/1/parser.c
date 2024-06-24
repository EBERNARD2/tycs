#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 2000 // Max size for line len
#define IN 1
#define OUT 0

char line[MAXLINE];
int len;
char stack[MAXLINE] = {0};
int stack_idx = 0;



void parser(void);
int get_line(void);
void push_stack(int c);
int pop_stack(void);


int main(void)
{
  extern int len;

  while((len = get_line()) > 0)
    parser();
}


void push_stack(int c) 
{

  extern char stack[];
  extern int stack_idx;

  stack[stack_idx++] = c;
}


int pop_stack(void)
{

  extern char stack[];
  extern int stack_idx;

  return stack[--stack_idx];

}

void parser(void)
{
  extern char line[];
  extern int len;
  extern char stack[];
  extern int stack_idx;
  
  int i, sin_quote_state, doub_quote_state, c;
  sin_quote_state = doub_quote_state = OUT;


  for (i = 0; i < len - 1; i++) {
    c = line[i];

    // if the current value is a single quote and both states are off 
        // set single quote state on and continue 
    if (c - '0' == 39 && !sin_quote_state && !doub_quote_state) {
      sin_quote_state = IN;
      continue;
    }
  
    // if the current value is a double quote and both states are off
      // set double quote state on and continue 
    if (c == '"' && !sin_quote_state && !doub_quote_state) {
      doub_quote_state = IN;
      continue;
    }
    

    // if the current value is a single quote and single quote value is on
      // set single quote state off and continue 
  
   if (c - '0' == 39 && sin_quote_state) {
      sin_quote_state = OUT;
      continue;
    }
    

    // if the current value is a double quote and double quote value is on
      // set double quote state off and continue 
    if (c == '"' && doub_quote_state) {
      doub_quote_state = OUT;
      continue;
    }
    

    if ((c == '}' || c == ']' || c == ']') && stack_idx == 0) {
      printf("Error: Cannot have closing brace %c before open brace.\n", c);
      return;
    }
    
    if (c ==  '}') {
      if (pop_stack() != '{') {
        printf("Error: '}' brackets must begin with oppening bracket '{'.\n");
        return;
      }
    }

     if (c ==  ')') {
      if (pop_stack() != '(') {
        printf("Error: ')' brackets must begin with oppening bracket '('.\n");
        return;
      }
    }

    if (c ==  ']') {
      if (pop_stack() != '[') {
        printf("Error: ']' brackets must begin with oppening bracket '[.'\n");
        return;
      }
    }
    
    // if value is an open bracket 
    // push value to bracket stack
    if (c == '[' || c == '(' || c == '{')
      push_stack(c);
    

    // if there are still values on the stack and current value is a comment
      // throw an error

    bool comment = (c == '/' && line[i + 1] == '/') || (c == '/' && line[i + 1] == '*');
    if (stack_idx > 0 && comment) {
      printf("Error: Must have closing bracket for %c \n", stack[stack_idx - 1]);
      return;
    }
    
    
    // if a valid single comment is made break out of loop - the parsing is done 
    if (c == '/' && line[i + 1] == '/')
      break;

    // if it is a valid multi line comment, look for closing tag(this is a rudimentary parse so we'll only check one line of input)

    if (c== '/' && line[i+1] == '*'){
      i += 2;
      while ((line[i] != '*' && line[i + 1] != '/') && i < len - 2)  
        i++;


      int end_comment = (line[i] != '*' && line[i + 1] != '/');
      if (!end_comment) {
        printf("Error: Quote must have ending\n");
        return;
      }
    }

  }

  if (stack_idx > 0) {
    printf("Error: opening quote must have closing quote\n");
    return;
  }

  printf("No syntax errors in line\n\n");
  
}


int get_line(void)
{
  extern char line[];
  extern int len;
  int i, c;

  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  
  if (c == '\n')
    line[i++] = c;
  
  line[i] = '\0';

  return i;
}