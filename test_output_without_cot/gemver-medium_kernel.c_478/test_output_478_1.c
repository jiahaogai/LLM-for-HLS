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
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
    }
    x[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      tmp += A[j][i] * v1[j];
    }
    y[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    z[i] += beta * y[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    w[i] = alpha * x[i] + u2[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * w[j];
    }
    z[i] = tmp + z[i];
  }
}