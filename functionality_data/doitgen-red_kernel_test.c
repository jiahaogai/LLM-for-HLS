#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_doitgen function
void kernel_doitgen(double A[25][20][30], double C4[30][30], double sum[30]);

int main() {
    double A[25][20][30], C4[30][30], sum[30];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize matrix A and C4 with random values
    for (int r = 0; r < 25; r++) {
        for (int q = 0; q < 20; q++) {
            for (int p = 0; p < 30; p++) {
                A[r][q][p] = (double)rand() / RAND_MAX * 100.0;  // Values between 0 and 100
            }
        }
    }

    for (int s = 0; s < 30; s++) {
        for (int p = 0; p < 30; p++) {
            C4[s][p] = (double)rand() / RAND_MAX * 100.0;  // Values between 0 and 100
        }
    }

    // Call the kernel_doitgen function
    kernel_doitgen(A, C4, sum);

    // Print some results to verify the function's behavior
    printf("Modified matrix A:\n");
    for (int r = 0; r < 25; r++) {
        for (int q = 0; q < 20; q++) {
            for (int p = 0; p < 30; p++) {
                if (p == 0) {  // Only print the first element of each row for brevity
                    printf("A[%d][%d][0] = %f\n", r, q, A[r][q][0]);
                }
            }
        }
        if (r == 2) break;  // Limit output to a few rows for readability
    }

    return 0;
}
