/* header files */
#include <stdio.h>
#include <math.h>
#include <float.h>

int main(void){
  double a,b,c,D;
  printf("The solution to ax^2 + bx + c = 0\n");
  printf("a: "); scanf("%lf",&a);
  printf("b: "); scanf("%lf",&b);
  printf("c: "); scanf("%lf",&c);

  D = b * b - 4 * a * c;

  //make the epsilon bigger or smaller depending on the b
  if (fabs(D) <= DBL_EPSILON * fabs(b * b)) {
    printf("A repeated root = %.30f\n", -b / (2 * a));
  } else if ( D > 0) {
    printf("Two real roots = %.30f, %.30f\n",
           (-b + sqrt(D)) / (2 * a),
           (-b - sqrt(D)) / (2 * a));
  } else {
    printf("Two complex roots = %.30f + %.30f i, %.30f - %.30f i\n",
           -b / (2 * a), sqrt(-D) / (2 * a),
           -b / (2 * a), sqrt(-D) / (2 * a));
  }

  return 0;
}