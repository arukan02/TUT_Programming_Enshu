/* header files */
#include <stdio.h>
#include <float.h>

/* main */
int main() {
    // Display precision constants
    printf("DBL_DIG: %d\n", DBL_DIG);
    printf("DBL_EPSILON: %.30f\n", DBL_EPSILON);

    // Rounding Error
    // The value 0.1 cannot be exactly represented in binary floating-point format.
    double rounding_error = 0.2 - 0.1;
    printf("Rounding error: %.30f\n", rounding_error);

    // Cancellation of Significant Digits
    // When subtracting two nearly equal numbers, significant digits can be lost.
    double b = 0.200006103515625;
    double cancellation_error = b - 0.2;
    printf("Cancellation of significant digits: %.20f\n", cancellation_error);

    // Loss of Information
    // When adding a small number to a large number, the small number can be lost due to the precision limits.
    double large_number = 1e16;
    double small_number = 1.0;
    double loss_of_information = large_number + small_number;
    printf("Loss of information: %.20f\n", loss_of_information);

    return 0;
}
