#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = 0.0;
    y[i] = 0.0;
    z[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[0] += u1[i] * A[i][0];
    y[0] += v1[i] * A[i][0];
    z[0] += A[i][0];
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400; j++) {
      x[0] += u1[i] * A[i][j];
      y[j] += v1[i] * A[i][j];
      z[0] += A[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    z[i] = beta * z[i] + y[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    x[i] = alpha * x[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 400; i++) {
    v2[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      v2[i] += A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 400; i++) {
    w[i] = u2[i] * v2[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 400; i++) {
    double tmp = (double )0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L8}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * w[j];
    }
    z[i] += tmp;
  }
}