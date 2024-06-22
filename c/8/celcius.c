#include <stdio.h>

int main(void)
{
  float fahr, celcius;
  float lower, upper, step;

  lower = 0;
  upper = 150;
  step = 10;

  celcius = lower;

  printf("***************************************\n");
  printf(" Celcius to Fahrenheit Conversion \n");
  printf("***************************************\n\n");


  while (celcius <= upper) {
    fahr = (9.0 / 5.0 * celcius) + 32;
    printf("%3.1f %6.0f\n", celcius, fahr);
    celcius += step;
  }

  return 0;
}