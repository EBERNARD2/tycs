#include <stdio.h>


int binsearch(int x, int v[], int n);

int main(void)
{
  return 0;
}


/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
  int low, high, mid;
  low = 0;
  high = n - 1;

  while (low < high) {
    mid = (low+high)/2;
    
    if (x > v[mid])
      low = mid + 1;
    else 
      high = mid;
  }

  return -1; /* no match */
}