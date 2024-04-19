#include <math.h>
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp3 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 50; j++) {
      tmp2 += A[i][j] * u2[j];
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 0; j < 50; j++) {
      w[j] = beta * w[j] + y[i] * tmp1 + z[i] * tmp3;
    }
    
#pragma ACCEL PARALLEL reduction=x[i] FACTOR=auto{__PARA__L4}
    for (j = 0; j < 50; j++) {
      x[i] += A[i][j] * w[j];
    }
    
#pragma ACCEL PARALLEL reduction=y[i] FACTOR=auto{__PARA__L5}
    for (j = 0; j < 50; j++) {
      y[i] += A[j][i] * v2[j] + x[j];
    }
    
#pragma ACCEL PARALLEL reduction=z[i] FACTOR=auto{__PARA__L6}
    for (j = 0; j < 50; j++) {
      z[i] += A[i][j] * v1[j];
    }
  }
}