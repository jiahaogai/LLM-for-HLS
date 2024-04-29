#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_syrk function
void kernel_syrk(double alpha, double beta, double C[80][80], double A[80][60]);

int main() {
    double C[80][80], A[80][60];
    double alpha = 1.2, beta = 0.5;

    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrix A with random values and matrix C with zero
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 60; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;  // Random values between 0 and 10
        }
    }

    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 80; j++) {
            C[i][j] = 0.0;  // Initialize C to zero
        }
    }

    // Call the kernel_syrk function
    kernel_syrk(alpha, beta, C, A);

    // Print some of the results to verify the function's behavior
    printf("Output matrix C (sample elements):\n");
    for (int i = 0; i < 80; i += 10) {  // Print every 10th row for brevity
        for (int j = 0; j <= i; j += 10) {  // Print every 10th column up to the diagonal
            printf("C[%d][%d] = %f\n", i, j, C[i][j]);
        }
    }

    return 0;
}
