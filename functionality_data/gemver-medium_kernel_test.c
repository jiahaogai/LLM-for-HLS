#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_gemver function
void kernel_gemver(int n, double alpha, double beta, double A[400][400], double u1[400], double v1[400], double u2[400], double v2[400], double w[400], double x[400], double y[400], double z[400]);

int main() {
    int n = 400;
    double alpha = 1.5, beta = 1.2;
    double A[400][400], u1[400], v1[400], u2[400], v2[400], w[400], x[400], y[400], z[400];

    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // Fill the arrays with random values
    for (int i = 0; i < n; i++) {
        u1[i] = (double)rand() / RAND_MAX;
        v1[i] = (double)rand() / RAND_MAX;
        u2[i] = (double)rand() / RAND_MAX;
        v2[i] = (double)rand() / RAND_MAX;
        y[i] = (double)rand() / RAND_MAX;
        z[i] = (double)rand() / RAND_MAX;
        w[i] = 0.0; // Initialize to 0 as they will accumulate values
        x[i] = 0.0; // Initialize to 0 as they will accumulate values
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Call the kernel_gemver function
    kernel_gemver(n, alpha, beta, A, u1, v1, u2, v2, w, x, y, z);

    // Print some results to verify function behavior
    printf("Output vector x:\n");
    for (int i = 0; i < n; i++) {
        if (i % 40 == 0) { // Print every 40th element to keep output manageable
            printf("x[%d] = %f\n", i, x[i]);
        }
    }
    printf("Output vector w:\n");
    for (int i = 0; i < n; i++) {
        if (i % 40 == 0) {
            printf("w[%d] = %f\n", i, w[i]);
        }
    }

    return 0;
}
