/* header files */
#include <stdio.h>
#include <float.h>

int main(void) {

double x, y, z;
printf("Enter x y z: ");
scanf("%lf%lf%lf", &x, &y, &z);

if (x + y - z <= (2 * DBL_EPSILON)) { //
puts("z is equal to x + y.");
} else {
puts("z is not equal to x + y.");
}
return 0;
}