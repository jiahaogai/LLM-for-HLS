

**Note**: This example references a BLAS library. BLAS is an external library and is not provided by ARM.

#pragma ACCEL kernel

void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
    }
  }
  
#pragma ACCEL PIPELINE auto{_in_4}
  
#pragma ACCEL TILE FACTOR=auto{16}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 220; j++) {
      double tmp = A[i][0] * B[0][j];
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (k = 1; k < 200; k++) {
        tmp += A[i][k] * B[k][j];
      }
      C[i][j] += alpha * tmp;
    }
  }
}