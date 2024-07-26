#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate P(A|B) using Bayes' theorem
double bayes(double pBgivenA, double pBgivenNotA, double pA) {
    double pNotA = 1.0 - pA;
    double pB = (pBgivenA * pA) + (pBgivenNotA * pNotA);
    return (pBgivenA * pA) / pB;
}

// Function to calculate P(A|B) using the Monte Carlo method
double bayes_monte(double pBgivenA, double pBgivenNotA, double pA) {
    long trials = 1000000;
    long truePositives = 0;
    long falsePositives = 0;

    for (long i = 0; i < trials; i++) {
        if ((double)rand() / RAND_MAX < pA) { // Person is infected
            if ((double)rand() / RAND_MAX < pBgivenA) { // Positive test
                truePositives++;
            }
        } else { // Person is not infected
            if ((double)rand() / RAND_MAX < pBgivenNotA) { // Positive test
                falsePositives++;
            }
        }
    }

    double totalPositives = truePositives + falsePositives;
    return (double)truePositives / totalPositives;
}

int main() {
    double pA = 1.0 / 5000;          // Prevalence of disease
    double pBgivenA = 0.99;          // True positive rate
    double pBgivenNotA = 1.0 - 0.98; // False positive rate

    // Calculate P(A|B) using Bayes' theorem
    double result_bayes = bayes(pBgivenA, pBgivenNotA, pA);
    printf("Bayesian inference P[A|B].\n");
    printf("P[B|A]: %.2f\n", pBgivenA);
    printf("P[B|~A]: %.2f\n", pBgivenNotA);
    printf("P[A]: %.5f\n", pA);
    printf("P[A|B] = %.6f\n", result_bayes);

    // Calculate P(A|B) using Monte Carlo method
    srand((unsigned int)time(NULL));
    double result_monte = bayes_monte(pBgivenA, pBgivenNotA, pA);
    printf("P[A|B] = %.6f (by Monte Carlo)\n", result_monte);

    return 0;
}
