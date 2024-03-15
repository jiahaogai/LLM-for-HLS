#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double u_ij = 0.0;
    
#pragma ACCEL PARALLEL reduction=u_ij FACTOR=auto{1}
    for (j = 0; j < 120; j++) {
      tmp1 = A[i][j] * u1[j] + v1[i] * A[i][j];
      u_ij += A[i][j] * v1[j];
      y[i] += A[i][j] * x[j];
    }
    e0: for (j = 0; j < 120; j++) {
      x[j] = alpha * ((2.0 * y[i]) - x[j] - u_ij);
      tmp2 += A[i][j] * x[j];
    }
    z[i] = beta * v2[i] + tmp1 + u1[i] * tmp2;
    w[i] = x[i] + y[i] + z[i];
  }
}