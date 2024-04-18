#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_mvt function
void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400]);

int main() {
    double x1[400] = {0}, x2[400] = {0}, y_1[400], y_2[400], A[400][400];

    // Initialize random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrices and vectors with random values
    for (int i = 0; i < 400; i++) {
        y_1[i] = (double)rand() / RAND_MAX * 10.0; // Values between 0 and 10
        y_2[i] = (double)rand() / RAND_MAX * 10.0;
        for (int j = 0; j < 400; j++) {
            A[i][j] = (double)rand() / RAND_MAX * 10.0;
        }
    }

    // Call the kernel_mvt function
    kernel_mvt(x1, x2, y_1, y_2, A);

    // Print some of the results to verify the function's behavior
    printf("Output vectors x1 and x2:\n");
    for (int i = 0; i < 400; i++) {
        if (i % 50 == 0) { // Print every 50th element to keep the output readable
            printf("x1[%d] = %f\n", i, x1[i]);
            printf("x2[%d] = %f\n", i, x2[i]);
        }
    }

    return 0;
}
