/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* functions */
double bisection(double front, double rear, double epsilon);
double f(double x);

/* main */
int main(void) {
  double front, rear, epsilon;
  int predicted_iterations;
  puts("An approximate solution to (x - 6)^3 + 8 = 0.");
  printf("Enter front and rear values with a space between them (front < rear): ");
  scanf("%lf%lf", &front, &rear);

  epsilon = 0.001;
  printf("The convergence epsilon is %6f\n", epsilon);

  predicted_iterations = (int)(log((rear - front) / epsilon) / log(2)) + 1;
  printf("The predicted iteration number is %d\n", predicted_iterations);
  printf("x = %f\n", bisection(front, rear, epsilon));

  return 0;
}

/* bisection method */
double bisection(double front, double rear, double epsilon) {
  double mid;
  int count;

  if (f(front) * f(rear) > 0) {
    puts("Invalid values were entered.");
    exit(1);
  }

  
  /* write search program here */
  count = 0;
  while ((rear - front) > epsilon) {
    mid = (front + rear) / 2;
    printf("%d f = %6f, r = %6f\n", count + 1, front, rear);
    if (f(mid) == 0.0) {
      return mid; 
    } else if (f(front) * f(mid) < 0) {
      rear = mid;
    } else {
      front = mid;
    }
    count += 1;
  }

  return front;
}

/* function to calculate (x - 6)^3 + 8 */
double f(double x) {
  return (x - 6) * (x - 6) * (x - 6) + 8;
}