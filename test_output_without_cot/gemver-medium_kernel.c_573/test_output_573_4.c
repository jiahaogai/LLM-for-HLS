#include <math.h>
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp2 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
    }

    y[i] = tmp;
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * v1[j];
    }

    x[i] = tmp2;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp3 FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp3 += A[j][i] * u2[j];
    }

    z[i] = tmp3;
    
#pragma ACCEL PARALLEL reduction=tmp4 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp4 += A[j][i] * v2[j];
    }

    w[i] = beta * w[i] + alpha * y[i] * x[i] + z[i];
  }
}