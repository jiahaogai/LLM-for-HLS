#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  gemv_1:
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{4}
    gemv_2:
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  gemv_3:
  for (i = 0; i < 400; i++) {
    x[i] = ((double )0);
    y[i] = 0.0;
    gemv_4:
    for (j = 0; j < 400; j++) {
      x[i] = x[i] + A[i][j] * w[j];
      y[i] = y[i] + A[i][j] * z[j];
    }
    x[i] = x[i] + beta * y[i];
    y[i] = y[i] + alpha * x[i];
  }
}