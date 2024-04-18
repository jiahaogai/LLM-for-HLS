#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_bicg function
void kernel_bicg(int m, int n, double A[410][390], double s[390], double q[410], double p[390], double r[410]);

int main() {
    int m = 410, n = 390;
    double A[410][390], s[390], q[410], p[390], r[410];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill matrix A, vectors p, and r with random values
    for (int i = 0; i < m; i++) {
        r[i] = (double)rand() / RAND_MAX * 100.0;  // Random values between 0 and 100 for r
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0;  // Random values between 0 and 100 for A
        }
    }

    for (int j = 0; j < n; j++) {
        p[j] = (double)rand() / RAND_MAX * 100.0;  // Random values between 0 and 100 for p
    }

    // Call the kernel_bicg function
    kernel_bicg(m, n, A, s, q, p, r);

    // Print the results to verify the function's behavior
    printf("Output vectors s and q:\n");
    printf("Vector s:\n");
    for (int j = 0; j < n; j++) {
        if (j % 20 == 0) { // Print every 20th element to keep output readable
            printf("s[%d] = %f\n", j, s[j]);
        }
    }
    printf("Vector q:\n");
    for (int i = 0; i < m; i++) {
        if (i % 20 == 0) { // Print every 20th element to keep output readable
            printf("q[%d] = %f\n", i, q[i]);
        }
    }

    return 0;
}
