- `double alpha`: Constant alpha used in the BLAS kernel.
- `double beta`: Constant beta used in the BLAS kernel.
- `double C[60][80]`: Matrix C used in the BLAS kernel.
- `double A[60][60]`: Matrix A used in the BLAS kernel.
- `double B[60][80]`: Matrix B used in the BLAS kernel.
- `int i`: Loop counter for the outer loop of the matrix multiplication.
- `int j`: Loop counter for the inner loop of the matrix multiplication.
- `int k`: Loop counter for the inner loop of the matrix multiplication.
- `double temp1`: Temporary variable used in the computation.
- `double temp2`: Temporary variable used in the computation.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{4}
      for (k = 0; k < 60; ++k) {
        temp1 += A[i][k] * B[k][j];
      }
      C[i][j] = temp1;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (k = 0; k < 60; ++k) {
        temp2 += A[k][i] * B[k][j];
      }
      C[i][j] = alpha * temp2 + beta * C[i][j];
    }
  }
}