#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = ((double )0);
    y[i] = ((double )0);
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    v1[i] = 0.0;
    for (j = 0; j < 400; j++) {
      v1[i] = (A[i][j] * u1[j] + v1[i]) ;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y[i] = 0.0;
    u2[i] = 0.0;
    for (j = 0; j < 400; j++) {
      y[i] = (A[i][j] * v2[j] + y[i]) ;
      u2[i] = (A[i][j] * u1[j] + u2[i]) ;
    }
    y[i] = y[i] + beta * u2[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    z[i] = 0.0;
    w[i] = 0.0;
    for (j = 0; j < 400; j++) {
      z[i] = (A[i][j] * x[j] + z[i]) ;
      w[i] = (A[i][j] * y[j] + w[i]) ;
    }
    w[i] = w[i] + alpha * x[i] * u1[i] + beta * z[i];
  }
}