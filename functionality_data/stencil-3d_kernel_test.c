#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the stencil3d function
void stencil3d(long C0, long C1, long orig[39304], long sol[32768]);

int main() {
    long C0 = 1, C1 = 2;  // Example constants
    long orig[39304], sol[32768]; // Declare arrays for original and solution

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Fill the original array with random values
    for (int i = 0; i < 39304; i++) {
        orig[i] = rand() % 100;  // Random values between 0 and 99
    }

    // Call the stencil3d function
    stencil3d(C0, C1, orig, sol);

    // Print some of the results to verify the function's behavior
    printf("Output array sol:\n");
    for (int i = 0; i < 32768; i++) {
        if (i % 1024 == 0) { // Print every 1024th element to keep output readable
            printf("sol[%d] = %ld\n", i, sol[i]);
        }
    }

    return 0;
}
