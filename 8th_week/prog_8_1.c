/* header files */
#include <stdio.h>

/* define */
#define MAX 15

/* functions */
int route( int v, int h, int save[MAX][MAX]);

/* main */
int main(void)
{
  int h, v;
  puts("The number of the shortest paths");
  printf("Enter the number of path in the vertical axis v (1 <= v <= %d): ", MAX);
  scanf ("%d", &v);
  printf("Enter the number of path in the horizontal axis h (1 <= h <= %d): ", MAX);
  scanf ("%d", &h);

  //initialize the save array
  int save[MAX][MAX];
  for(int i = 0; i < MAX; ++i)
    for(int j = 0; j < MAX; ++j)
      save[i][j] = -1;
  
  printf("The answer is %d.\n", route(v - 1, h - 1, save));
  return 0;
}

/* full search */
int route( int v, int h, int save[MAX][MAX]) {
  if (v == 0 || h == 0) {
    return 1;
  } 
  if(save[v][h] != -1) {
    return save[v][h];
  }

  //search for save if not found
  save[v][h] = route(v - 1, h, save) + route(v, h - 1, save);
  return save[v][h];
}