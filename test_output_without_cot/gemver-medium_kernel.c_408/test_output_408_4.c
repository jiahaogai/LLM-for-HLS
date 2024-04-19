#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[40],double x[50],double y[40],double z[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{8}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      w[i] += alpha * A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 50; j++) {
      z[i] += w[i] * v2[j] + y[i] * v1[j];
    }
  }
}