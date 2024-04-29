#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_syr2k function
void kernel_syr2k(double alpha, double beta, double C[80][80], double A[80][60], double B[80][60]);

int main() {
    double C[80][80], A[80][60], B[80][60];
    double alpha = 1.25, beta = 1.35;

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrices A, B, and C with random values
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 60; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;  // Values between 0 and 10
            B[i][j] = (double)rand() / RAND_MAX * 10.0;  // Values between 0 and 10
        }
        for (int j = 0; j < 80; j++) {
            C[i][j] = (double)rand() / RAND_MAX * 10.0;  // Values between 0 and 10
        }
    }

    // Call the kernel_syr2k function
    kernel_syr2k(alpha, beta, C, A, B);

    // Print the updated lower triangle of matrix C to verify correctness
    printf("Updated matrix C (lower triangle):\n");
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%8.2f", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
