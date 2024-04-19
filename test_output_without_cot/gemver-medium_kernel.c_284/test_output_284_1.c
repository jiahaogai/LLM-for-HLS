#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
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
    for (j = 0; j < 50; j++) {
      tmp3 += A[i][j] * u2[j];
    }
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{120}
    for (j = 0; j < 40; j++) {
      x[j] = beta * x[j] + y[i] * tmp1 + z[i] * tmp3;
    }
    
#pragma ACCEL PARALLEL reduction=tmp4 FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      tmp4 += A[i][j] * x[j];
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 50; j++) {
      w[j] = beta * w[j] + v2[i] * tmp2 + x[i] * tmp4;
    }
  }
}