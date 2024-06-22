#include <stdio.h>

int main(void)
{
  float fahr, celcius;
 
  printf("***************************************\n");
  printf(" Celcius to Fahrenheit Conversion \n");
  printf("***************************************\n\n");

  for (celcius = 150; celcius >= 0; celcius-=10)
    printf("%3.1f %6.0f\n", celcius, (9.0 / 5.0 * celcius) + 32);

  return 0;
}