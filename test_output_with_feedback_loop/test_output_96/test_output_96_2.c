#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    for (j = 0; j < 120; j++) {
      A[i][j] += + u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    y[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    z[i] = 0.0;
    double tmp = 0.0;
    for (j = 0; j < 120; j++) {
      if (i == j) {
        A[i][j] = 1.0;
      }
      y[i] += A[i][j] * w[j];
      x[i] += A[j][i] * w[j];
      z[i] += A[i][j] * v1[j];
      tmp += A[i][j] * u1[j] * v2[i];
    }
    y[i] = alpha * y[i] + beta * tmp + u1[i] * x[i] + u2[i] * z[i];
  }
}