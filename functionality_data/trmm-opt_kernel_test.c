#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_trmm function
void kernel_trmm(double alpha, double A[60][60], double B[60][80]);

int main() {
    double A[60][60], B[60][80], alpha;

    // Initialize random number generator for reproducibility
    srand((unsigned int)time(NULL));

    // Set the scalar alpha
    alpha = 2.0;

    // Initialize matrix A (lower triangular as per problem statement)
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            if (j <= i) { // Lower triangular and diagonal elements
                A[i][j] = (double)rand() / RAND_MAX * 10.0;
            } else {
                A[i][j] = 0.0; // Upper part is zero since it's triangular
            }
        }
    }

    // Initialize matrix B with random values
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 80; j++) {
            B[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // Print initial state of matrix B for reference
    printf("Matrix B before TRMM:\n");
    for (int i = 0; i < 5; i++) {  // Print the first 5 rows only to keep output readable
        for (int j = 0; j < 5; j++) { // Print the first 5 columns only
            printf("%f ", B[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Call the kernel_trmm function
    kernel_trmm(alpha, A, B);

    // Print results
    printf("Matrix B after TRMM:\n");
    for (int i = 0; i < 5; i++) {  // Again, print the first 5 rows
        for (int j = 0; j < 5; j++) { // And the first 5 columns
            printf("%f ", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}
