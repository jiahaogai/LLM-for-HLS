#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the ellpack function
void ellpack(double nzval[4940], int cols[4940], double vec[494], double out[494]);

int main() {
    double nzval[4940], vec[494], out[494];
    int cols[4940];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill the non-zero values and column indices for the ELLPACK format matrix
    for (int i = 0; i < 4940; i++) {
        nzval[i] = (double)rand() / RAND_MAX * 100.0; // Non-zero values
        cols[i] = rand() % 494; // Column indices within bounds
    }

    // Initialize the vector to be multiplied
    for (int i = 0; i < 494; i++) {
        vec[i] = (double)rand() / RAND_MAX * 100.0;
        out[i] = 0.0; // Start with an output vector of zeros
    }

    // Call the ellpack function
    ellpack(nzval, cols, vec, out);

    // Print some of the results to verify the function's behavior
    printf("Output vector out:\n");
    for (int i = 0; i < 494; i++) {
        if (i % 50 == 0) { // Print every 50th element to keep output readable
            printf("out[%d] = %f\n", i, out[i]);
        }
    }

    return 0;
}
