#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_atax function
void kernel_atax(int m, int n, double A[116][124], double x[124], double y[124], double tmp[116]);

int main() {
    int m = 116, n = 124;
    double A[116][124], x[124], y[124], tmp[116];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrix A and vector x with random values
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    for (int j = 0; j < n; j++) {
        x[j] = (double)rand() / RAND_MAX * 10.0;
        y[j] = 0.0;  // Ensuring y starts with zero as expected by the algorithm
    }

    // Call the kernel_atax function
    kernel_atax(m, n, A, x, y, tmp);

    // Print some elements of vector y to verify correctness
    printf("After kernel_atax:\n");
    for (int j = 0; j < 10; j++) {  // Just print the first 10 elements for simplicity
        printf("y[%d] = %f\n", j, y[j]);
    }

    return 0;
}
