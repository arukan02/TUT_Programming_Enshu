/* header files */
#include <stdio.h>
#include <float.h>
#include <math.h>

int main(void) {

double x, y, z;
printf("This program calculates √(x^2 + y^2) - y\n");
printf("Enter x y: ");
scanf("%lf%lf", &x, &y);

double calc = sqrt( x * x + y * y) - y;
printf("√(x^2 + y^2) - y = %.20f\n", calc);

return 0;
}