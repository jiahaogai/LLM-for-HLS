#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[50],double u2[40],double v2[50],double w[50],double x[40],double y[50],double z[40])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    z[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      z[i] = z[i] + A[i][j] * v1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 40; i++) {
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L7}
    for (j = 0; j < 50; j++) {
      y[i] = y[i] + A[i][j] * u1[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 40; i++) {
    x[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L8}
    for (j = 0; j < 50; j++) {
      x[i] = x[i] + A[j][i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L9}
    for (j = 0; j < 50; j++) {
      w[j] = w[j] + alpha * A[i][j] * x[i] + beta * y[i];
    }
  }
}