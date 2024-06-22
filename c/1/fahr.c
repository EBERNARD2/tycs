#include <stdio.h>

#define UPPER 300
#define STEP 20

float convert_to_celcius(float fahr); 

int main(void)
{
  float fahr, celcius;

  fahr = 0; 

  for (; fahr < UPPER; fahr += STEP)
    printf("%3.0f %2.2f\n", fahr, convert_to_celcius(fahr));


  return 0;
}


float convert_to_celcius(float fahr) {
  return (5.0 / 9.0) * (fahr - 32.0);
}