#include "MathsTools.h"
#include <stdio.h>
/**
 * @brief return a power b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int power(double a, double b)
{
  int res = 1;
  for (int i = 0; i < b; i++)
  {
    res *= a;
  }
  return res;
}
/**
 * @brief rerun n in binary
 * 
 * @param n 
 */
void *binarySumFromInt(int n)
{
  int i = 0;
  while (n > 0)
  {
    if (n % 2 == 1)
    {
      printf("%d+", power(2, i));
    }
    n /= 2;
    i++;
  }
}
