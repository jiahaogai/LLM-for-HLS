c
 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp2 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp3 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp3 += A[i][j] * u2[j];
    }
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (j = 0; j < 400; j++) {
      z[i] += alpha * A[i][j] * v2[j] + tmp1 * v1[j] + tmp2 * w[j];
    }
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      w[i] += alpha * A[j][i] * v1[j] + tmp3 * v2[j];
    }
  }
}