/* header files */
#include <stdio.h>

/* functions */
int pow_loop(int x, int y); // 関数宣言
int pow_recf(int x, int y); // 関数宣言

/* main */
int main(void) {
int x, y;
printf("The calculation of x to the power y, x^y\n");
printf("The exponent of a positive integer x (space) y: ");
scanf("%d%d", &x, &y);
printf("LOOP %d^%d = %d\n", x, y, pow_loop(x, y));
printf("RECF %d^%d = %d\n", x, y, pow_recf(x, y));
return 0;
}

/*exponential function using for loop*/
int pow_loop(int x, int y) {
    int i, result = 1;
    for (i=y; i >=1; i--){
        result *= x;
    }
    return result;
}

/*exponential function using recursive*/
int pow_recf(int x, int y) {
    if(y==0){
        return 1;
    } else {
        return x * pow_recf(x , y - 1);
    }
}
