10. `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L2}`: Performs a reduction operation of `C` variable across loop iterations with automatic determination of parallelization factor at level 2 to optimize computation and resource usage.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1 = 0.0;
  double temp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (k = 0; k < 60; k++) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (k = 0; k < 80; k++) {
        temp2 += alpha * B[k][j] * A[i][k];
      }
      C[i][j] = beta * C[i][j] + temp1 + temp2;
    }
  }
}