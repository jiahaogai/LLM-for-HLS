c
 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 400; i++) {
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double du = 0.0;
    double dv = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp1 += A[i][j] * u1[j];
      du += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp2 += A[i][j] * v2[j];
      dv += A[i][j] * u2[j];
    }
    z[i] = tmp1 + du * alpha + beta * y[i];
    w[i] = tmp2 + dv * alpha;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double x_tmp = 0.0;
    double y_tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=x_tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x_tmp += A[j][i] * u1[j];
    }
    
#pragma ACCEL PARALLEL reduction=y_tmp FACTOR=auto{32}
    for (j = 0; j < 400; j++) {
      y_tmp += A[j][i] * v1[j];
    }
    x[i] = x_tmp;
    y[i] = beta * y_tmp + z[i];
  }
}