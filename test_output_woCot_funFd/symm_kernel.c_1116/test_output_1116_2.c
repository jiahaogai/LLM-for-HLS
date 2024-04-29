- `C[i][j] *= beta`: Scales the elements of the matrix C with the scalar `beta` using the BLAS function `dscal`.
- `C[i][j] += alpha * temp1`: Performs the matrix-vector multiplication operation `C[i][j] += alpha * temp1` using the BLAS function `daxpy`.
- `temp2 = 0`: Initializes the variable `temp2` with the scalar `0` to avoid propagation of stale data.
- `temp1[k] *= B[j][k]`: Scales each element of the vector `temp1` with the corresponding element of the matrix `B` using the BLAS function `dscal`.
- `temp2 += A[i][k] * temp1[k]`: Performs the matrix-vector multiplication operation `temp2 += A[i][k] * temp1[k]` to update the variable `temp2` using the BLAS function `daxpy`.
- `C[i][j] = temp2`: Updates the value of `C[i][j]` using the value of `temp2` to allow the final matrix multiplication to be computed in one loop.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1[60];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      temp1[i] = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{4}
      for (k = 0; k < 60; ++k) {
        temp1[i] += A[i][k] * B[k][j];
      }
      C[i][j] *= beta;
      C[i][j] += alpha * temp1[i];
    }
  }
}