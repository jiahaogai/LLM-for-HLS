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
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{32}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp2 += A[i][j] * v1[j];
    }
    w[i] = tmp1;
    x[i] = tmp2;
    tmp3 = 0.0;
    tmp4 = 0.0;
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp3 += A[j][i] * u2[j];
      tmp4 += A[j][i] * v2[j];
    }
    y[i] = beta * y[i] + tmp3 + alpha * x[i] * w[i];
    z[i] = beta * z[i] + tmp4 + alpha * x[i] * v2[i];
  }
}