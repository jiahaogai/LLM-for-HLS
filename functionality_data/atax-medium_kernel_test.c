#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_atax function
void kernel_atax(double A[390][410], double x[410], double y[410], double tmp[390]);

int main() {
    double A[390][410], x[410], y[410], tmp[390];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill matrix A and vector x with random values
    for (int i = 0; i < 390; i++) {
        for (int j = 0; j < 410; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
        }
    }
    for (int j = 0; j < 410; j++) {
        x[j] = (double)rand() / RAND_MAX * 100.0; // Values between 0 and 100
    }

    // Call the kernel_atax function
    kernel_atax(A, x, y, tmp);

    // Print some of the results to verify the function's behavior
    printf("Output vector y:\n");
    for (int j = 0; j < 410; j++) {
        if (j % 20 == 0) { // Print every 20th element to keep output readable
            printf("y[%d] = %f\n", j, y[j]);
        }
    }

    return 0;
}
