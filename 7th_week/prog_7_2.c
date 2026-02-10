/* header files */
#include <stdio.h>
#include <stdlib.h>

/* functions */
double bisection(double front, double rear);
double f(double x);

/* main */
int main(void) {
  double front, rear;
  puts("An approximate solution to (x - 6)^3 + 8 = 0.");
  printf("Enter front and rear values with a space between them (front < rear): ");
  scanf("%lf%lf", &front, &rear);

  printf("x = %f\n", bisection(front, rear));

  return 0;
}

/* bisection method */
double bisection(double front, double rear) {
  double mid, eps = 0.001;

  if (f(front) * f(rear) > 0) {
    puts("Invalid values were entered.");
    exit(1);
  }

  /* write search program here */
  while ((rear - front) > eps) {
    mid = (front + rear) / 2;
    if (f(mid) == 0.0) {
      return mid; 
    } else if (f(front) * f(mid) < 0) {
      rear = mid;
    } else {
      front = mid;
    }
  }

  return front;
}

/* function to calculate (x - 6)^3 + 8 */
double f(double x) {
  return (x - 6) * (x - 6) * (x - 6) + 8;
}