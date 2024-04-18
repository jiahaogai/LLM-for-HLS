#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of kernel_bicg function
void kernel_bicg(int m, int n, double A[410][390], double s[390], double q[410], double p[390], double r[410]);

int main() {
    int m = 410, n = 390;
    double A[410][390], s[390], q[410], p[390], r[410];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrix A with random values, vectors p and r with random values
    for (int i = 0; i < m; i++) {
        r[i] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        }
    }
    for (int j = 0; j < n; j++) {
        p[j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        s[j] = 0.0; // Initialize s to zero
    }

    // Initialize q to zero
    for (int i = 0; i < m; i++) {
        q[i] = 0.0;
    }

    // Call the kernel_bicg function
    kernel_bicg(m, n, A, s, q, p, r);

    // Print some results to verify the function's behavior
    printf("Output vectors s and q:\n");
    for (int i = 0; i < n; i++) {
        if (i % 20 == 0) { // Print every 20th element to keep output readable
            printf("s[%d] = %f\n", i, s[i]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (i % 20 == 0) { // Print every 20th element to keep output readable
            printf("q[%d] = %f\n", i, q[i]);
        }
    }

    return 0;
}
