/* header files */
#include <stdio.h>

/* define */
#define MAX 15

/* functions */
int route( int v, int h);

/* main */
int main(void)
{
  int h, v;
  puts("The number of the shortest paths");
  printf("Enter the number of path in the vertical axis v (1 <= v <= %d): ", MAX);
  scanf ("%d", &v);
  printf("Enter the number of path in the horizontal axis h (1 <= h <= %d): ", MAX);
  scanf ("%d", &h);
  printf("The answer is %d.\n", route(v - 1, h - 1));
  return 0;
}

/* full search */
int route( int v, int h) {
  if (v == 0 || h == 0) {
    return 1;
  } else {
    return route(v - 1, h) + route(v, h - 1);
  }
}