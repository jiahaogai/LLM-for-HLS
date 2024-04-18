#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_bicg function
void kernel_bicg(int m, int n, double A[124][116], double s[116], double q[124], double p[116], double r[124]);

int main() {
    int m = 124, n = 116;
    double A[124][116], s[116], q[124], p[116], r[124];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrices and vectors with random values
    for (int i = 0; i < m; i++) {
        r[i] = (double)rand() / RAND_MAX * 100.0; // Random values between 0 and 100 for vector r
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0; // Random values between 0 and 100 for matrix A
        }
    }

    for (int j = 0; j < n; j++) {
        p[j] = (double)rand() / RAND_MAX * 100.0; // Random values between 0 and 100 for vector p
    }

    // Call the kernel_bicg function
    kernel_bicg(m, n, A, s, q, p, r);

    // Print results for verification
    printf("Output vector s:\n");
    for (int j = 0; j < n; j++) {
        if (j % 10 == 0) { // Print every 10th element to keep output readable
            printf("s[%d] = %f\n", j, s[j]);
        }
    }
    printf("\nOutput vector q:\n");
    for (int i = 0; i < m; i++) {
        if (i % 10 == 0) { // Print every 10th element to keep output readable
            printf("q[%d] = %f\n", i, q[i]);
        }
    }

    return 0;
}
