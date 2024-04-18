#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_gesummv function
void kernel_gesummv(double alpha, double beta, double A[250][250], double B[250][250], double tmp[250], double x[250], double y[250]);

int main() {
    double A[250][250], B[250][250], tmp[250], x[250], y[250];
    double alpha = 1.5, beta = 1.2;

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrices A and B, and vector x with random values
    for (int i = 0; i < 250; i++) {
        for (int j = 0; j < 250; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;  // Random values between 0 and 10
            B[i][j] = (double)rand() / RAND_MAX * 10.0;  // Random values between 0 and 10
        }
        x[i] = (double)rand() / RAND_MAX * 10.0;  // Random values between 0 and 10
    }

    // Call the kernel_gesummv function
    kernel_gesummv(alpha, beta, A, B, tmp, x, y);

    // Print the results in the vector y to verify the function's behavior
    printf("Output vector y after kernel_gesummv:\n");
    for (int i = 0; i < 250; i++) {
        if (i % 25 == 0) {  // Print every 25th element to keep the output manageable
            printf("y[%d] = %f\n", i, y[i]);
        }
    }

    return 0;
}
