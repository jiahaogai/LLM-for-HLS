#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaration of the kernel_fdtd_2d function
void kernel_fdtd_2d(int tmax, int nx, int ny, double ex[200][240], double ey[200][240], double hz[200][240], double _fict_[100]);

int main() {
    int tmax = 100, nx = 200, ny = 240;
    double ex[200][240], ey[200][240], hz[200][240], _fict_[100];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Initialize the matrices ex, ey, and hz with random values
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            ex[i][j] = (double)rand() / RAND_MAX;
            ey[i][j] = (double)rand() / RAND_MAX;
            hz[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Initialize the _fict_ array with random values
    for (int t = 0; t < 100; t++) {
        _fict_[t] = (double)rand() / RAND_MAX;
    }

    // Call the kernel function
    kernel_fdtd_2d(tmax, nx, ny, ex, ey, hz, _fict_);

    // Output some results for validation
    printf("Sample outputs after kernel_fdtd_2d execution:\n");
    printf("ex[100][120] = %f\n", ex[100][120]);
    printf("ey[100][120] = %f\n", ey[100][120]);
    printf("hz[100][120] = %f\n", hz[100][120]);

    return 0;
}
