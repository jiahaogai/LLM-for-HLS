#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_symm function
void kernel_symm(double alpha, double beta, double C[60][80], double A[60][60], double B[60][80]);

int main() {
    double alpha = 1.2, beta = 0.8;
    double C[60][80], A[60][60], B[60][80];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrices A (symmetric), B, and C with random values
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0;
            if (j > i) {
                A[j][i] = A[i][j]; // Ensure A is symmetric
            }
        }
        for (int j = 0; j < 80; j++) {
            B[i][j] = (double)rand() / RAND_MAX * 100.0;
            C[i][j] = (double)rand() / RAND_MAX * 100.0;
        }
    }

    // Call the kernel_symm function
    kernel_symm(alpha, beta, C, A, B);

    // Print the results to verify the function's behavior
    printf("Output matrix C:\n");
    for (int i = 0; i < 5; i++) { // Print the first 5 rows for brevity
        for (int j = 0; j < 5; j++) { // Print the first 5 columns of each row
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
