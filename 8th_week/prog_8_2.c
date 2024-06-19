/* header files */
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

/* define */
#define MAX 40

/* functions */
long route(long r[MAX][MAX], int v, int h);

void run_route(int v, int h) {
  long route_result[MAX][MAX] = {};
  route(route_result, v - 1, h - 1);
}

/* main */
int main(void)
{
  int h, v;
  long route_result[MAX][MAX] = {};
  struct timeval start, end;

  puts("The number of the shortest paths");
  printf("Enter the number of path in the vertical axis v (1 <= v <= %d): ", MAX);
  scanf ("%d", &v);
  printf("Enter the number of path in the horizontal axis h (1 <= h <= %d): ", MAX);
  scanf ("%d", &h);

  gettimeofday(&start, NULL);
  printf("The answer is %ld.\n", route(route_result, v - 1, h - 1));
  for(int i = 0; i < 999; i++) {
    run_route(v - 1, h - 1);
  }
  gettimeofday(&end, NULL);
  printf("\nTime taken by route(dynamic programming)%f s.\n",
         (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0e-6);

  return 0;
}

/* dynamic programming */
long route(long r[MAX][MAX], int v, int h) {
  int i, j;
  r[0][0] = 1;
  for (i = 0; i <= v; i++) {
    for (j = 0; j <= h; j++) {
      if (i != 0) { // add if not at the first vertical line
        r[i][j] += r[i - 1][j];
      }
      if (j != 0) { // add if not at the first horizontal line
        r[i][j] += r[i][j - 1];
      }
    }
  }
  return r[v][h];
}