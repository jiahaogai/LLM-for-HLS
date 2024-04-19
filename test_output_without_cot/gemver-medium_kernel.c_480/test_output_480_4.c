#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[40][50],double u1[40],double v1[40],double u2[50],double v2[50],double w[40],double x[50],double y[40],double z[50])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L4}
    for (j = 0; j < 50; j++) {
      x[i] += beta * A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L5}
    for (j = 0; j < 50; j++) {
      z[i] += alpha * A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 40; i++) {
    w[i] = u1[i] + v1[i] + u2[i] + v2[i] + z[i];
  }
}