#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400][400],double v1[400][400],double u2[400][400],double v2[400][400],double w[400][400],double x[400][400],double y[400][400],double z[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      A[i][j] += + u1[i][j] * v1[i][j] + u2[i][j] * v2[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      x[i][j] += + alpha * A[j][i] * x[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      y[i][j] += + beta * A[i][j] * y[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i][j] += + x[i][j] * y[i][j];
    }
  }
}