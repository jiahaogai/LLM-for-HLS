- `C[i][j] += alpha * A[i][k] * B[k][j]`: Basic operation in matrix multiplication. The order of the indices is adjusted based on the row-major storage of C and the row-major storage of A and B.
- `temp1 = 0`: Initialization of temporary variable `temp1` before reduction.
- `temp1 += A[i][k] * B[k][j]`: Reduction operation in the inner loop.
- `C[i][j] += beta * temp1`: Post-reduction scaling and addition to `C[i][j]`.
- `temp2 = 0`: Initialization of temporary variable `temp2` before reduction.
- `temp2 += temp1`: Reduction operation in the middle loop.
- `temp2`: Post-reduction scaling and addition to `temp2` for storing results.

#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        double temp2 = 0.0;
        for (auto l = 0; l < 60; l++) {
          temp1 += A[i][l] * B[l][j];
        }
        temp2 = alpha * temp1 + beta * C[k][j];
        C[k][j] = temp2;
      }
    }
  }
//#pragma endscop
}