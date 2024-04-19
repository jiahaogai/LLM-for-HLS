#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{2}
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x[i] = x[i] + A[i][j] * w[j];
    }
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      y[i] = y[i] + A[j][i] * w[j];
    }
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{16}
    for (j = 0; j < 400; j++) {
      z[i] = z[i] + A[i][j] * x[j];
    }
  }
}