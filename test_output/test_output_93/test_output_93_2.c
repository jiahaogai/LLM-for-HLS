

**/
 
#include <math.h>
#ifndef CELL_SIZE
#define CELL_SIZE 80
#endif // CELL_SIZE
#ifndef N
#define N 400
#endif // N
#ifndef NUM_ITERS
#define NUM_ITERS 40
#endif // NUM_ITERS
  
double A[400];
double B[400];

void kernel_jacobi_1d(int tsteps,int n,double A[400],double B[400])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (i = 1; i < 400 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 400 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
  }
//#pragma endscop
}
