#include <math.h>
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      A[i][j] += + u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
    for (j = 0; j < 400; j++) {
      x[i] += A[i][j] * w[j];
      y[i] += A[i][j] * x[j];
      z[i] += A[i][j] * v2[j];
    }
    y[i] = alpha * y[i] + beta * z[i] + u1[i] * x[i] + v1[i] * y[i];
  }
}