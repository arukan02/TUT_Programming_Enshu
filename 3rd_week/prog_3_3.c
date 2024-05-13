/* header files */
#include <stdio.h>
#include <math.h>

/* functions */
int power(int x, int y); // 関数宣言

/* main */
int main(void) {
int x,y;
printf("The calculation of x to the power y, x^y.\n");
printf("Enter integers x and y (x > 0, y >= 1) with a space between them: ");
scanf("%d%d", &x, &y);
printf("%d^%d = %d", x, y, power(x,y));
return 0;
}

/*exponential function using recursive*/
int power(int x, int y) {
    if (y == 0) {
        return 1;
    } else if (y % 2 == 0) {
        printf("recf\n");
        double temp = power(x, y / 2);
        return temp * temp;
    } else {
        printf("recf\n");
        double temp = power(x, (y - 1) / 2);
        return x * temp * temp;
    }
}
