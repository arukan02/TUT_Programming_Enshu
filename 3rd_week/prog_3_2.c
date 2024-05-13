#include <stdio.h>

/* Function declarations */
void factorize(int n, int divisor);

/* Main function */
int main(void) {
    int n;
    printf("Prime factorization.\n");
    printf("Enter a positive integer n (2 <= n <= 10000):  ");
    scanf("%d", &n);
    printf("%d = ", n);
    factorize(n,2);
    return 0;
}

/* Recursive function to factorize with prime number */
void factorize(int n, int divisor) {
    if(n == 1){
        return;
    }
    if (n % divisor == 0) {
        if (n != divisor) {
            printf("%d x ", divisor); // Print the factor with "x" separator
        } else {
            printf("%d", divisor); // Print the last factor without "x" separator
        }
        factorize(n / divisor, divisor); 
    } else {
        factorize(n, divisor + 1); 
    }
}