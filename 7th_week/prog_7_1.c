/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* define */
#define N 30     // the number of array elements
#define MAX 100  // the range of elements (1 - MAX)

/* functions */
int binary(int array[], int target);
void quick_sort(int array[], int front, int rear);

/* main */
int main(void) {
  int target, array[N], i;
  srand((unsigned int )time(NULL)); // set seed for randomization
  for (i = 0; i < N; i++) {
    array[i] = rand() % MAX + 1;
  }
  quick_sort(array, 0, N - 1);

  puts("An array of integers in ascending order.");
  for (i = 0; i < N; i++) {
    printf("%d ", array[i]);
  }
  printf("\nBinary search for the target: ");
  scanf("%d", &target);

  if (binary(array, target) == 1) {
    printf("The target %d was found.\n", target);
  } else {
    printf("The target %d was Not found.\n", target);
  }
  return 0;
}

/* binary search */
int binary(int array[], int target) {
  int front = 0, rear = N - 1;

  /* write search program here */
    while (front <= rear) {
        int mid = (front + rear) / 2;
        if (array[mid] == target) {
            return 1; // Target found
        } else if (array[mid] < target) {
            front = mid + 1; // Search the right half
        } else {
            rear = mid - 1; // Search the left half
        }
    }

  return 0;
}

/* example_5_2.c*/
#define SWAP(type_, xx, yy) { type_ temp = xx; xx = yy; yy = temp; }
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
  int pivot, pindex, f, r;
  f = front; r = rear;
  pindex = (f + r)/2;
  pivot = array[ pindex ]; /* pivot selection */
  do {
    while (f <= rear  && array[f] <  pivot) {  f++; }
    while (r >= front && array[r] >= pivot) {  r--; }
    if (f <= r) {
      SWAP(int, array[f], array[r]);
      f++;
      r--;
    }
  } while (f <= r);
  if (r < front) { // there is no element less than pivot
    SWAP(int, array[front], array[pindex]);
    quick_sort(array, front+1, rear);
  } else {
    if (front < r) {
      quick_sort(array, front, r);
    }
    if (f < rear)  {
      quick_sort(array, f, rear);
    }
  }
}