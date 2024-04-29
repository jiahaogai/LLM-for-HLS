#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the stencil function
void stencil(int orig[8192], int sol[8192], int filter[9]);

int main() {
    int orig[8192], sol[8192], filter[9];
    int i;

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill the original data array with random values
    for (i = 0; i < 8192; i++) {
        orig[i] = rand() % 256; // Random values between 0 and 255
    }

    // Define a simple 3x3 filter for the stencil operation
    filter[0] = 0; filter[1] = 1; filter[2] = 0;
    filter[3] = 1; filter[4] = -4; filter[5] = 1;
    filter[6] = 0; filter[7] = 1; filter[8] = 0;

    // Call the stencil function
    stencil(orig, sol, filter);

    // Print some of the results to verify the function's behavior
    printf("Output (sol) array sampled values:\n");
    for (i = 0; i < 128*64; i += 64) { // Sample some rows from the solution array
        printf("sol[%d] = %d\n", i, sol[i]);
    }

    return 0;
}
