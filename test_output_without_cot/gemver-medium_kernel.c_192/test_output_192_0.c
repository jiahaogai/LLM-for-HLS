#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    z[i] = 0.0;
    y[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    z[i] = 0.0;
    y[i] = 0.0;
    for (j = 0; j < 400; j++) {
      z[i] = z[i] + alpha * A[i][j] * v1[j];
      y[i] = y[i] + alpha * A[i][j] * u1[j];
    }
    y[i] = y[i] + beta * v2[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    w[i] = 0.0;
    x[i] = 0.0;
    for (j = 0; j < 400; j++) {
      w[i] = w[i] + alpha * A[j][i] * v2[j];
      x[i] = x[i] + alpha * A[j][i] * u2[j];
    }
    w[i] = w[i] + beta * y[i];
  }
}