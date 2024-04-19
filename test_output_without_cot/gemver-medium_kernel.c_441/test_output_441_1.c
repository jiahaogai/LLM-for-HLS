#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      x[i] += A[i][j] * u1[j];
      tmp += A[i][j] * v1[j];
    }
    y[i] += tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      y[i] += A[i][j] * u2[j];
      tmp += A[i][j] * v2[j];
    }
    z[i] += tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    z[i] = beta * z[i] + alpha * y[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp = 0.0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp += A[i][j] * x[j];
    }
    w[i] = tmp;
  }
}