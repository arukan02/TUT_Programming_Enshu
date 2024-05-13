/* header files */
#include <stdio.h>
#include <stdlib.h>

/* define */
#define ARRAY_MAX 5
#define STR_MAX 256

/* structure */
typedef struct queue {
  int array[ARRAY_MAX];
  int front;
  int end;
} Queue;

/* declearation functions */
void enqueue(Queue *x);
void dequeue(Queue *x);
void print_queue(Queue *x);
int find_next(int current); /* For Assignment 3.1 */

/* for debug */
void print_detailed_queue(Queue *x);

/* main */
int main(void) {
  /* Variables */
  Queue x;
  int num;
  char str[STR_MAX];

  /* Initial settings */
  x.front = 0;
  x.end = 0;

  /* Main loop */
  while(1) { /* Infinite loop */
    puts("Enter the operation number.");
    printf("1. Enqueue, 2. Dequeue, 3. Print, 4. Exit: ");
    fgets(str, sizeof(str), stdin);
    num = atoi(str);
    // selected operation for Queue x
    switch(num) {
    case 1: enqueue(&x);
      break;
    case 2: dequeue(&x);
      break;
    case 3: print_queue(&x);
      break;
    case 4: exit(0);
    case 9: print_detailed_queue(&x); /* not explained */
      break;
    default: printf("-- You input wrong key [%d] --", num);
    }
  }
  return 1;
}

/* enqueue */
void enqueue(Queue *x) {
  char str[STR_MAX];
  if (find_next(x->end) == x->front) {
    puts("-- No resource remained. --");
  } else {
    printf("Input a number to enqueue: ");
    fgets(str, sizeof(str), stdin);
    x->array[x->end] = atoi(str);
    x->end = find_next(x->end);
  }
}

/* dequeue */
void dequeue(Queue *x) {
  if (x->front == x->end) {
    puts("-- There is no data. --");
  } else {
    printf("Dequeue: %d\n", x->array[x->front]);
    x->front = find_next(x->front);
  }
}

/* print all data */
void print_queue(Queue *x) {
  int i;
  if (x->front == x->end) {
    puts("-- There is no data. --");
  } else {
    while (1){
        if(x->front == x->end) {
            break;
        }
        else {
            printf("%d ",x->array[x->front]);
            x->front = find_next(x->front);
        }
    }
    putchar('\n');
  }
}

int find_next(int current){
    if (current == ARRAY_MAX - 1){
        return 0;
    }
    else {
        return current + 1;
    }
}

/* print all data (detailed) */
void print_detailed_queue(Queue *x) {
  int i;
  for (i = 0; i < ARRAY_MAX; i++) {
    if ((x->front < x->end) && (x->front <= i) && (i < x->end)) {
      /* 終端に到達していない時 */
      printf("%3.3d : %3.3d : %d\n", i, i - x->front, x->array[i]); 
    } else if ((x->front > x->end) && (x->front >= i) && (x->end < i)) {
      /* 終端を超えた時 */
      printf("%3.3d : %3.3d : %d\n", i, i - x->end, x->array[i]);
    } else {
      /* No data */
      printf("%3.3d : ***\n", i);
    }
  }
}