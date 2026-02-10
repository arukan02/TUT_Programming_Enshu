#include <stdio.h>

/* Function declarations */
int primeCheck(int n);
int prime(int n, int divisor);

/* Main function */
int main(void) {
    int n;
    printf("Prime number judgement.\n");
    printf("Enter an integer n (1 <= n <= 1000000): ");
    scanf("%d", &n);
    if (primeCheck(n)) {
        printf("%d is a prime number.\n", n);
    } else {
        printf("%d is not a prime number.\n", n);
    }
    return 0;
}

/* Function to check if a number is prime */
int primeCheck(int n) {
    if (n <= 1) {
        return 0; // Numbers less than or equal to 1 are not prime
    }
    return prime(n, 2); // Start checking divisors from 2
}

/* Recursive function to determine if a number is prime */
int prime(int n, int divisor) {
    if (divisor * divisor > n) {
        return 1; // If divisor exceeds the square root of n, n is prime
    }
    if (n % divisor == 0) {
        return 0; // If n is divisible by divisor, it's not prime
    }
    return prime(n, divisor + 1); // Recursively call prime with the next divisor
}