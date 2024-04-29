#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_symm function
void kernel_symm(double alpha, double beta, double C[200][240], double A[200][200], double B[200][240]);

int main() {
    double alpha = 1.2, beta = 0.8;
    double C[200][240], A[200][200], B[200][240];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill matrices A, B, and C with random values
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        }
        for (int j = 0; j < 240; j++) {
            B[i][j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
            C[i][j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        }
    }

    // Call the kernel_symm function
    kernel_symm(alpha, beta, C, A, B);

    // Print some of the results to verify the function's behavior
    printf("Modified matrix C:\n");
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 240; j++) {
            if ((i % 20 == 0) && (j % 30 == 0)) { // Print a subset of the matrix elements to keep output manageable
                printf("C[%d][%d] = %f\n", i, j, C[i][j]);
            }
        }
    }

    return 0;
}
