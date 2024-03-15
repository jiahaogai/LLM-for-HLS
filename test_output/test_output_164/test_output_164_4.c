

5. "Map A to B" - Use `#pragma ACCEL kernel FACTOR=auto{__PARA__L1}` to autoparallelize the L1 operation.

6. " #pragma ACCEL PIPELINE auto{off}"
/*
  This test case is a simplified version of matmul.c. It uses row-major
  to show how ACCEL PIPELINE work.
  Original from MATMUL subroutine in:
  
  Wilkes, D. L. (1995). "A protocol for testing parallel algorithms".
  In Proceedings of the 1995 ACM SIGPLAN symposium on Parallel
  programming (PP'95). ACM, New York, NY, USA, 96-106.
  http://doi.acm.org/10.1145/202374.202381
*/

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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L3}
      for (j = 0; j < 220; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
