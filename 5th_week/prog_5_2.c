/* Example of quick sort */
/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* define */
#define N 20    // the number of array elements
#define MAX 40  // the range of elements (1 - MAX)
#define SWAP(type_, xx, yy) { type_ temp = xx; xx = yy; yy = temp; }

/* for debug */
int check_sorted(int original[], int sorted[], int n);

/* functions */
void quick_sort(int array[], int front, int rear);

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
  puts("\nSorting by quick sort.");
  gettimeofday(&start, NULL);
  quick_sort(array, 0, N-1);
  gettimeofday(&end, NULL);

  /* print result */
  for (i = 0; i < N; i++) {
    printf("%d ", array[i]);
  }

  /* show processing time */
  printf("\nTime taken by quick sort %f s.\n",
         (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0e-6);

  /* check validation */
  i = check_sorted(original, array, N);
  if (i == 0) {
    puts("### Warning ###   Sort Failed");
    return 1;
  }

  return 0;
}

/* function version of swap */
void int_swap(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

/* sorting by quick sort */
void quick_sort(int array[], int front, int rear) {
  // for 2 elements
  if (rear - front == 1) {
    if (array[front] > array[rear]) {
      int diff = array[front];
      array[front] = array[rear];
      array[rear] = diff;
    }
    return;
  }
  // more than 2 elements
  int pivot, pindex, f, r;
  f = front; r = rear;
  pindex = (f + r)/2;
  pivot = array[ pindex ]; /* pivot selection */
  do {
    while (f <= rear  && array[f] <  pivot) {  f++; }
    while (r >= front && array[r] >= pivot) {  r--; }
    if (f <= r) {
      printf(" %d <-> %d\n", array[f], array[r]);
      SWAP(int, array[f], array[r]);
      // OR // int_swap(&(array[f]), &(array[r]));
      f++;
      r--;
    }
  } while (f <= r);
  printf("[%d %d] / [%d %d]\n", front, r, f, rear);

  if (r < front) {
    // there is no element less than pivot
  } else {
    // there are two part for next step
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