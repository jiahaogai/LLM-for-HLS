#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[40],double x[50],double y[40],double z[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{3}
    for (j = 0; j < 50; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp2 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp3 FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      tmp3 += A[i][j] * y[j];
    }
    w[i] = tmp1;
    x[i] = tmp2;
    y[i] = alpha * tmp3 + beta * z[i];
    z[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{8}
    for (j = 0; j < 50; j++) {
      z[i] += A[i][j] * x[j];
      w[i] += A[i][j] * v2[j];
    }
  }
}