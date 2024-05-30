/* Example of bubble sort */
/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* define */
#define N 30     // the number of array elements
#define MAX 100  // the range of elements (1 - MAX)

/* for debug */
int check_sorted(int original[], int sorted[], int n);

/* functions */
void bubble_sort(int array[], int n);

/* main */
int main(void) {
  int i, original[N], array[N];
  struct timeval start, end;        // structures for time measurement

  /* making random array */
  srand((unsigned int )time(NULL)); // set seed for randomization
  puts("An array of integers in random order.");
  for (i = 0; i < N; i++) {
    array[i] = rand() % MAX + 1;
    original[i] = array[i];
    printf("%d ", array[i]); /* print initial */
  }

  /* process sorting */
  puts("\nSorting by bubble sort.");
  gettimeofday(&start, NULL);
  bubble_sort(array, N);
  gettimeofday(&end, NULL);

  /* print result */
  for (i = 0; i < N; i++) {
    printf("%d ", array[i]);
  }

  /* show processing time */
  printf("\nTime taken by bubble sort %f s.\n",
         (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0e-6);

  /* check validation */
  i = check_sorted(original, array, N);
  if (i == 0) {
    puts("### Warning ###   Sort Failed");
    return 1;
  }

  return 0;
}

/* sorting by bubble sort */
void bubble_sort(int array[], int n) {
  int i, j, temp;
  for (i = 0; i <= n - 1; i++) {
    for (j = n - 1; j >= i; j--) {
      if(array[i]>array[j]){
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

/* debug */
int check_sorted(int original[], int sorted[], int n)
{
  int i,j,key;
  int *flag;
  flag = (int *)malloc(sizeof(int) * n);
  for(i = 0; i < n; i++) {
    flag[i] = 0;
  }
  /* */
  int res = 0;
  for(i = 0; i < n; i++) {
    key = sorted[i];
    for(j = 0; j < n; j++) {
      if(key == original[j] && flag[j] == 0) {
        flag[j] = 1;
        break;
      }
    }
    if(j==n) {
      printf("invalid sorted %d, %d\n", i, key);
      free(flag);
      return 0;
    }
  }
  /* */
  int prev = sorted[0];
  for(i = 1; i < n; i++) {
    if (sorted[i] < prev) {
      printf("sort failed %d, %d\n", i, sorted[i]);
      free(flag);
      return 0;
    }
    prev = sorted[i];
  }
  /* */
  free(flag);
  return 1;
}