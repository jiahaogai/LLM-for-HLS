 #pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[120][120],double u1[120],double v1[120],double u2[120],double v2[120],double w[120],double x[120],double y[120],double z[120])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    double tmp = 0.0;
    double u = 0.0;
    double v = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
    for (j = 0; j < 120; j++) {
      tmp += A[i][j] * u1[j];
      u += A[i][j] * v1[j];
    }
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L5}
    for (j = 0; j < 120; j++) {
      x[i] += A[i][j] * w[j];
    }
    v = v1[i];
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (j = 0; j < 120; j++) {
      z[i] += A[i][j] * y[j];
    }
    y[i] = beta * y[i] + alpha * u * v + tmp;
  }
}
