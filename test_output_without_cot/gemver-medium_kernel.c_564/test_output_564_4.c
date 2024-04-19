#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = ((double )0);
    y[i] = ((double )0);
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    v1[i] = 0.0;
    u1[i] = 0.0;
    for (j = 0; j < 120; j++) {
      x[i] += A[i][j] * v2[j];
      y[i] += A[i][j] * u2[j];
      v1[i] += A[i][j] * y[j];
      u1[i] += A[i][j] * x[j];
      z[i] += A[i][j] * ((double )(u2[j] * v2[j]));
    }
    z[i] = beta * z[i] + alpha * u1[i] + v1[i];
  }
}