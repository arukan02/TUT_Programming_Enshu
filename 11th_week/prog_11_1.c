/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* main */
int main(void) {
    long n;
    puts("Calculating pi");
    printf("Loop counts n: ");
    scanf("%ld", &n);

    long i;
    long counter = 0;
    double x, y;
    srand((unsigned int)time(NULL));
    
    for (i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1) {
            counter++;
        }
    }

    double pi_estimate = 4.0 * ((double)counter / n);
    printf("Estimated pi = %lf\n", pi_estimate);

    return 0;
}