#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_jacobi_1d function
void kernel_jacobi_1d(int tsteps, int n, double A[120], double B[120]);

int main() {
    int tsteps = 40, n = 120;
    double A[120], B[120];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize arrays A and B with random values
    for (int i = 0; i < n; i++) {
        A[i] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        B[i] = 0.0; // Initially set all elements of B to zero
    }

    // Call the kernel_jacobi_1d function
    kernel_jacobi_1d(tsteps, n, A, B);

    // Print the results to verify the function's behavior
    printf("Final output array A:\n");
    for (int i = 0; i < n; i++) {
        if (i % 10 == 0) { // Print every 10th element to keep output readable
            printf("A[%d] = %f\n", i, A[i]);
        }
    }

    return 0;
}
