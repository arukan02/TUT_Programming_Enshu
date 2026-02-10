/* headers */
#include <stdio.h>
#include <stdlib.h>

/* struct definition */
typedef struct queue {
  double array[5];
  int front;
  int end;
} Queue;

/* pass-by-value */
void func_variable(int x)
{
  x = -1;
}
/* pass-by-reference */
void func_pointer(int *ptr)
{
  *ptr = -1;
}

int main()
{
  int x = 10;
  int y = 20;
  int *ptr = &x;

  printf("sizeof(char)      == %ld\n", sizeof(char));
  printf("sizeof(short)     == %ld\n", sizeof(short));
  printf("sizeof(int)       == %ld\n", sizeof(int));
  printf("sizeof(long)      == %ld\n", sizeof(long));
  printf("sizeof(long long) == %ld\n", sizeof(long long));
  printf("sizeof(float)     == %ld\n", sizeof(float));
  printf("sizeof(double)    == %ld\n", sizeof(double));

  printf("sizeof(int*)      == %ld\n", sizeof(int*));
  puts("");

  /* what is XX*/
  printf("*ptr / %d == XX\n", *ptr);

  /* waht is ??*/
  printf("&x[%lx] ?? ptr[%lx]\n", (unsigned long)&x, (unsigned long)ptr);

  /* what is XX*/
  func_variable(x);
  printf("after func_variable // x == XX == %d\n", x);

  /* what is XX*/
  func_pointer(&x);
  printf("after func_pointer // x == XX == %d\n", x);

  /* what is XX*/
  printf("*ptr / %d == XX\n", *ptr);

  ptr = &y;
  /* what is XX*/
  printf("*ptr / %d == XX\n", *ptr);

  /* waht is ??*/
  printf("&x[%lx] ?? ptr[%lx]\n", (unsigned long)&x, (unsigned long)ptr);

  /* waht is ??*/
  printf("&y[%lx] ?? ptr[%lx]\n", (unsigned long)&y, (unsigned long)ptr);

  /* what is XX*/
  func_variable(y);
  printf("after func_variable // x == XX == %d\n", y);

  /* what is XX*/
  func_pointer(&y);
  printf("after func_pointer // x == XX == %d\n", y);

  /* what is XX*/
  printf("*ptr / %d == XX\n", *ptr);

  return 0;
}
