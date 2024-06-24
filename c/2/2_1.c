#include <stdio.h>
#include <limits.h>


void get_char_min_max(void);
void get_int_min_max(void);
void get_long_min_max(void);
void get_float_min_max(void);
void get_double_min_max(void);


int main(void)
{

  printf("Char Max: %d\t\t", CHAR_MAX);
  printf("Char Min: %d\t\t", CHAR_MIN);
  printf("\n");
  printf("Short Max: %d\t\t", SHRT_MAX);
  printf("ShortMin: %d\t\t", SHRT_MIN);
  printf("\n");
  printf("Int Max: %d\t\t", INT_MAX);
  printf("Int Min: %d\t\t",INT_MAX);
  printf("\n");
  printf("Long Max: %ld\t\t", LONG_MAX);
  printf("Long Min: %ld\t\t", LONG_MIN);
  printf("\n");

  get_char_min_max();
  get_int_min_max();
  get_long_min_max();


  return 0;
}



// 10000000 --> 11111111

void get_char_min_max(void)
{

  printf("Max signed char computed: %d\n\n", (signed char) 0x7F);
  printf("Min signed char computed %d\n", (signed char) 0x80);
  printf("Max unsigned char computed: %d\n\n", (unsigned char) 0xFF);

}


void get_int_min_max(void)
{

  printf("Max signed int computed: %d\n\n", (signed int) 0x7FFFFFFF);
  printf("Min signed int computed %d\n", (signed int) 0x80000000);
  printf("Max unsigned int computed: %d\n\n", (unsigned int) 0xFFFFFFFF);
  
}

void get_long_min_max(void)
{
  printf("Max signed long computed: %ld\n", (signed long) 0x7FFFFFFFFFFFFFFF);
  printf("Min signed long computed %ld\n", (signed long) 0x8000000000000000);
  printf("Max unsigned long computed: %ld\n", (unsigned long) 0xFFFFFFFFFFFFFFFF);
}


void get_short_min_max(void)
{
  printf("Max signed short computed: %d\n\n", (signed short) 0x7FFF);
  printf("Min signed short co mputed %d\n", (signed short) 0x8000);
  printf("Max unsigned short computed: %d\n\n", (unsigned short) 0xFFFF);
}

