/* header files */
#include <stdio.h>

//Macro, define constant
#define ARRAY_SIZE 46

/* functions */
int fibonacci(int fibo[], int n); // 関数宣言

/* main */
int main(void) {
int n;
int fibo[ARRAY_SIZE] = {0,1,1}; //initialized by 0
printf("Fibonacci number f(n) = f(n - 1) + f(n - 2).\n");
printf("Enter a positive integer n (1 <= n <= 45): ");
scanf("%d", &n);
printf("f(%d) = %d\n", n, fibonacci(fibo, n));
return 0;
}

/*exponential function using for loop*/
int fibonacci(int fibo[], int n) {
    if (n==1 || n==2){
        return fibo[n];
    } else if (fibo[n] != 0) { // Check if the value is already calculated and stored
        return fibo[n];
    } else {
        fibo[n] = fibonacci(fibo, n - 1) + fibonacci(fibo, n - 2);
        return fibo[n];
    }
}
