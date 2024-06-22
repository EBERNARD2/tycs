#include <stdio.h>


int main(void)
{
  float fahr, celcius;
  float lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  fahr = lower;

  printf("***************************************\n");
  printf(" Fahrenheight to Celcius Conversion \n");
  printf("***************************************\n\n");


  while (fahr <= upper) {
    celcius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celcius);
    fahr += step;
  }

  return 0;
}