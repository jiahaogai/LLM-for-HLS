#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[50],double x[40],double y[50],double z[40])
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
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp1 += A[i][j] * u1[j];
      tmp4 += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp3 FACTOR=auto{8}
    for (j = 0; j < 50; j++) {
      tmp2 += A[i][j] * u2[j];
      tmp3 += A[i][j] * v2[j];
    }
    
#pragma ACCEL PARALLEL reduction=x[i:auto{1}] FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
    x[i] = x[i] + alpha * ((u1[0] * tmp1) + (v1[0] * tmp4));
    
#pragma ACCEL PARALLEL reduction=z[i:auto{1}] FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      z[i] += A[i][j] * (w[j] * v2[j] + u2[j] * tmp3);
    }
    z[i] = z[i] + alpha * ((v1[0] * tmp2) + (u1[0] * tmp3));
  }
}