/* header files */
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

/* define */
#define MAX 40

/* functions */
long route(long r[MAX][MAX], int v, int h, int blocked[MAX][MAX]);

void run_route(int v, int h, int blocked[MAX][MAX]) {
  long route_result[MAX][MAX] = {};
  route(route_result, v - 1, h - 1, blocked);
}

/* main */
int main(void)
{
  int h, v, b, x, y;
  long route_result[MAX][MAX] = {};
  struct timeval start, end;

  puts("The number of the shortest paths");
  printf("Enter the number of path in the vertical axis v (1 <= v <= %d): ", MAX);
  scanf ("%d", &v);
  printf("Enter the number of path in the horizontal axis h (1 <= h <= %d): ", MAX);
  scanf ("%d", &h);

  //initialize blocked array
  int blocked[MAX][MAX] = {};

  printf("Enter the number of blocked intersections: ");
  scanf("%d", &b);
  for(int i = 0; i < b; i++){
    printf("enter the coordinates of blocke intersection %d (x y): ", i + 1);
    scanf("%d %d", &x, &y);
    if (x >= 0 && x < v && y >= 0 && y < h){
      blocked[x][y] = 1;
    }
  }

  gettimeofday(&start, NULL);
  printf("The answer is %ld.\n", route(route_result, v - 1, h - 1, blocked));
  for(int i = 0; i < 999; i++) {
    run_route(v - 1, h - 1, blocked);
  }
  gettimeofday(&end, NULL);
  printf("\nTime taken by route(dynamic programming)%f s.\n",
         (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0e-6);

  return 0;
}

/* dynamic programming */
long route(long r[MAX][MAX], int v, int h, int blocked[MAX][MAX]) {
  int i, j;
  //start point consideration
  r[0][0] = blocked[0][0] ? 0 : 1;

  for (i = 0; i <= v; i++) {
    for (j = 0; j <= h; j++) {
      if (blocked[i][j]) { 
        r[i][j] = 0;
      } else {
        if (i != 0){
          r[i][j] += r[i - 1][j];
        }
        if (j != 0) { // add if not at the first horizontal line
          r[i][j] += r[i][j - 1];
        }
      }
    }
  }
  return r[v][h];
}