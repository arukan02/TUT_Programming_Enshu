/* C言語の振り返り */
/* header files */
#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 256

/* function declarations */
int function_name(int x, int y);

/* main */
int main(void) {
    int x, y, z;
    double fval;
    char str[STR_SIZE];

    // comment
    puts("Input floating-point value: ");// puts
    fgets(str, sizeof(str), stdin); // fgets
    fval = atof(str); // atof, atoi
    printf("fval = %f\n", fval); // printf

    /* comment */
    puts("This is an example.");         // puts
    printf("Input integers x and y : "); // printf
    scanf("%d%d", &x, &y);               // scanf
    printf("get integer x = %d, y = %d\n", x, y);

    puts("");
    puts("--- example of function call ---");
    z = function_name(x, y); // function call
    printf("z = %d\n", z);

    //
    //
    puts("");
    puts("--- example of if ---");
    if (x < y) {
        printf("x(%d) < y(%d)\n", x, y);
    } else if (x == y) {
        printf("x(%d) == y(%d)\n", x, y);
    } else if ((x % y) == 0) {
        printf("x(%d) %% y(%d) == 0\n", x, y);
    } else if (fval < 0.0) {
        printf("%f < 0.0\n", fval);
    } else {
        puts("all conditions are false.");
    }

    //
    //
    puts("");
    puts("--- example of for ---");
    int i;
    for(i = 0; i < 5; i++) { // i++  :=> i = i + 1
        printf("i = %d\n", i);
    }

    //
    //
    puts("");
    puts("--- example of while ---");
    while( x > 0 ) {
        printf("x = %d\n", x);
        x = x - 10;
        printf(">>> x = %d\n", x);
    }
    printf("finished: x = %d\n", x);
    return 0;
}

/* definition of function */
int function_name(int x, int y)
{
    int ret = x + y;
    printf("function_name(%d, %d) returns %d\n", x, y, ret);
    return ret;
}
