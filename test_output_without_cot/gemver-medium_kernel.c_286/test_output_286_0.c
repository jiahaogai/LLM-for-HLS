#include <math.h>
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{3}
    for (j = 0; j < 50; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{30}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 50; i++) {
    x[i] = x[i] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L9}
    for (j = 0; j < 50; j++) {
      w[i] += alpha * A[i][j] * x[j];
    }
  }
}