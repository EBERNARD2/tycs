#include <stdio.h>
#include <string.h>
#include <math.h>


int htoi(char s[]);


int main(void)
{

  printf("%d\n", htoi("0x123456"));

  return 0;
}


int htoi(char s[])
{

  int i, ms_hex, exp, len, magnitude, num, sum;

  ms_hex = exp = 0;

  if((s[0] == '0' && s[1] == 'x') || (s[0] == '0' && s[1] == 'x'))
    ms_hex = 2;

  len = strlen(s);


  for ( i = len - 1; i >= ms_hex; i--) {
    magnitude = pow(16, exp);

    if (s[i] >= 48 && s[i] <= 57)
      num = s[i] - 48;
    else if (s[i] >= 65 && s[i] <= 70)
      num = s[i] - 55;
    else if (s[i] >= 97 && s[i] <= 102)
      num = s[i] - 87;
    else {
      printf("Invalid hex number\n");
      break;
    }

    sum += magnitude * num;
    exp++;

  }

    return sum;
  }
