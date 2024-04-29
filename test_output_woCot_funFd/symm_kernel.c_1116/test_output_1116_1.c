- `C[i][j] *= beta`: Scales the elements of matrix `C` with value `beta`.
- `C[i][j] += alpha * temp1`: Accumulates the partial results `temp1` to the elements of matrix `C` with value `alpha`.
- `for`: C/C++ loop tag.
- `i`: Loop variable.
- `j`: Loop variable.
- `k`: Loop variable.
- `A[i][k]`: C/C++ array subscript.
- `B[k][j]`: C/C++ array subscript.
- `temp1`: Loop variable.
- `temp2`: Loop variable.

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
      C[i][j] *= beta;
      C[i][j] += alpha * temp1;
    }
  }
}