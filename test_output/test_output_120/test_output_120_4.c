

**/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
  }
//#pragma endscop
}
int main(int argc,char **argv)
{
  double A[120];
  double B[120];
  int t;
  int i;
// Standardize the format across platforms
  for (t = 0; t < 40; t++) {
    for (i = 0; i < 120; i++) {
      A[i] = ((double )1);
      B[i] = ((double )0);
    }
    kernel_jacobi_1d(70,120,A,B);
  }
/*
    BENCHMARK INFORMATION
    kernel_jacobi_1d
      Time = 0.544489
    
    Number of bytes spilled = 248
*/
  return 0;
}
