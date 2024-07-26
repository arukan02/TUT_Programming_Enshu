/* header files */
#include <stdio.h>
#include <stdlib.h>

/* define */
#define MAX 10001
#define MAX_UNITS 10

/* functions */
void coins(int coin_types[], int n, int x);

/* main */
int main(void) {
  int num_units;
  int coin_types[MAX_UNITS];
  int x;

  puts("The calculation of the number of coins.");
  printf("How many units do you use? ");
  scanf("%d", &num_units);

  coin_types[0] = 1;  // The first currency unit is always 1
  puts("The first currency unit is 1.");
  for (int i = 1; i < num_units; i++) {
    printf("Enter %dth currency unit: ", i + 1);
    scanf("%d", &coin_types[i]);
  }

  printf("Enter an amount of money x (1 <= x <= 10000): ");
  scanf("%d", &x);

  coins(coin_types, num_units, x);

  return 0;
}

/* dynamic programming */
void coins(int coin_types[], int n, int x) {
  int i, j;
  int array[MAX];
  int coin_count[MAX][MAX_UNITS] = {0};  // To keep track of each coin usage

  /* initialize array */
  array[0] = 0;
  for (i = 1; i <= x; i++) {
    array[i] = MAX;
  }

  for (i = 0; i <= x; i++) {
    if (array[i] != MAX) {
      for (j = 0; j < n; j++) {
        int next = i + coin_types[j];
        if (next <= x && array[next] > array[i] + 1) {
          array[next] = array[i] + 1;
          for (int k = 0; k < n; k++) {
            coin_count[next][k] = coin_count[i][k];
          }
          coin_count[next][j]++;
        }
      }
    }
  }

  printf("The number of coins.\n");
  for (j = 0; j < n; j++) {
    printf("%d %d\n", coin_types[j], coin_count[x][j]);
  }
}
