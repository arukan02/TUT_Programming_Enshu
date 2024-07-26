#include <stdio.h>
#include <math.h>

#define SIGMA_SQ 0.1
#define ALPHA 1.8
#define EPSILON 1e-6
#define MAX_ITER 10000

double integrand(double x, double v) {
    return tanh(x / sqrt(v) + 1 / v) * tanh(x / sqrt(v) + 1 / v) * (1 / sqrt(2 * M_PI)) * exp(-x * x / 2);
}

double simpsons_integral(double v, double a, double b, int n) {
    if (n % 2 != 0) n++; // Ensure that n is even
    double h = (b - a) / n;
    double sum = integrand(a, v) + integrand(b, v);

    for (int i = 1; i < n; i += 2) {
        sum += 4 * integrand(a + i * h, v);
    }
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * integrand(a + i * h, v);
    }

    return sum * h / 3.0;
}

double MSE(double v) {
    return 1 - simpsons_integral(v, -10, 10, 10000); // Adjust integration limits and steps as needed
}

double equation(double v) {
    return v - (SIGMA_SQ + ALPHA * MSE(v));
}

double bisection(double a, double b, double tol) {
    double c;
    int iter = 0;
    printf("Sign change detected in interval (%.6f, %.6f)\n", a, b);
    do {
        c = (a + b) / 2;
        iter++;
        printf("Iteration=%d, solution=%.6f, error=%.6f\n", iter, c, fabs(equation(c)));
        if (fabs(equation(c)) <= tol) {
            return c;
        }
        if (equation(c) * equation(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    } while ((b - a) >= tol && iter < MAX_ITER);
    return c;
}

int main() {
    double v1 = bisection(SIGMA_SQ, (SIGMA_SQ + ALPHA) / 3, EPSILON);
    printf("Solution in interval (%.2f, %.2f): %.6f\n", SIGMA_SQ, (SIGMA_SQ + ALPHA) / 3, v1);

    double v2 = bisection((SIGMA_SQ + ALPHA) / 3, 2 * (SIGMA_SQ + ALPHA) / 3, EPSILON);
    printf("Solution in interval (%.2f, %.2f): %.6f\n", (SIGMA_SQ + ALPHA) / 3, 2 * (SIGMA_SQ + ALPHA) / 3, v2);

    double v3 = bisection(2 * (SIGMA_SQ + ALPHA) / 3, SIGMA_SQ + ALPHA, EPSILON);
    printf("Solution in interval (%.2f, %.2f): %.6f\n", 2 * (SIGMA_SQ + ALPHA) / 3, SIGMA_SQ + ALPHA, v3);

    return 0;
}
