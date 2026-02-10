/* 〇課題6.2 */
/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DEBUG 0

/* define */
#define MAX 100 // the range of elements (1 - MAX)

/* functions */
void merge(int array[], int temp[], int front, int rear);

/* for debug */
int check_sorted(int original[], int sorted[], int n);

/* main */
int main(int argc, char **argv) {
  int *array;
  int *original;
  int *temp;
  int n = 30;
  int i;
  struct timeval start, end;        // structures for time measurement

  if (argc > 1) {
    n = atoi(argv[1]);
  }
  array = (int *)malloc(sizeof(int) * n);
  temp  = (int *)malloc(sizeof(int) * n);
  original = (int *)malloc(sizeof(int) * n);

  srand((unsigned int )time(NULL)); // set seed for randomization
  for (i = 0; i < n; i++) {
    original[i] = array[i] = rand() % MAX + 1;
  }
#ifdef DEBUG
  puts("An array of integers in random order.");
  for (i = 0; i < n; i++) {
//      array[i] = rand() % MAX + 1;
    printf("%d ", array[i]);
  }
  puts("\nSorting by merge sort.");
#endif

  gettimeofday(&start, NULL);
  merge(array, temp, 0, n - 1);
  gettimeofday(&end, NULL);

#ifdef DEBUG
  for (i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
#endif
  printf("\nTime taken by merge sort: %f s.\n",
         (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1.0e-6);

#ifdef DEBUG
  /* check validation */
  i = check_sorted(original, array, n);
  if (i == 0) {
    puts("### Warning ###   Sort Failed");
    return 1;
  }
#endif
  return 0;
}

/* sorting by merge sort */
void merge(int array[], int temp[], int front, int rear) {
  int mid, cur_f, cur_m, i;
#if DEBUG
  printf("*** merge called by front = %d, rear = %d, mid = %d: ",
         front, rear, (front + rear) / 2);
  for (i = front; i <= rear; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif
  // return if front is equal to rear (only one element)
  if (front == rear) {
    return;
  }

  // update mid with a value intermediate between front and rear
  mid = (front + rear) / 2;

  // recursive calls of the function merge() in the range
  // from front to mid, and from mid + 1 to rear, respectively
  merge(array, temp, front, mid);
  merge(array, temp, mid + 1, rear);
#if DEBUG
  printf("\tStart merging with f = %d, m = %d: ", front, mid + 1);
#endif
  // copy the array data to the temporal array
  for (i = front; i <= rear; i++) {
    temp[i] = array[i];
#if DEBUG
    printf("%d ", temp[i]);
#endif
  }
#if DEBUG
  printf("\n");
#endif
  cur_f = front;
  cur_m = mid + 1;

  // merge the two halves of the array in ascending order
  i = front;
    while(cur_f <= mid && cur_m <= rear){
      if(temp[cur_f] <= temp[cur_m]){
        array[i] = temp[cur_f];
        cur_f += 1;
      }
      else{
        array[i] = temp[cur_m];
        cur_m += 1;
      }
      i++;
    }
    while(cur_f <= mid){
      array[i] = temp[cur_f];
      cur_f += 1;
      i++;
    }
    while(cur_m <= rear){
      array[i] = temp[cur_m];
      cur_m += 1;
      i++;
    }
  
  
  /*
  Write merge process here
  */

#if DEBUG
  printf("\tEnd merge: ");
  for (i = front; i <= rear; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif
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