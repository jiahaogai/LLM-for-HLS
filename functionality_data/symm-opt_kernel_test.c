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

    // Initialize matrix A (symmetric), matrix B, and matrix C with random values
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0;  // Values between 0 and 100
            if (j < i) {
                A[j][i] = A[i][j];  // Ensure the matrix is symmetric
            }
        }
    }

    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            B[i][j] = (double)rand() / RAND_MAX * 100.0;  // Values between 0 and 100
            C[i][j] = (double)rand() / RAND_MAX * 100.0;  // Values between 0 and 100
        }
    }

    // Call the kernel_symm function
    kernel_symm(alpha, beta, C, A, B);

    // Print some of the results to verify the function's behavior
    printf("Modified matrix C after kernel_symm:\n");
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            if ((i + j) % 20 == 0) {  // Print every 20th element to keep output readable
                printf("C[%d][%d] = %f\n", i, j, C[i][j]);
            }
        }
    }

    return 0;
}
