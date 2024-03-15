7. Turn off automatic loop blocking for the following loop.
8. Use the original, full form of the loop without breaking it into smaller chunks.
9. Run the iterations of the loop with a parallel factor of 4.
10. Run the iterations of the first inner loop with a parallel factor of 4.
11. Run the iterations of the second inner loop with a parallel factor of 4.
12. Turn off automatic loop fusion for the following loop.
13. Use the original, full form of the loop without breaking it into smaller chunks.
14. Run the iterations of the loop with a parallel factor of 2.
15. Run the iterations of the first inner loop with a parallel factor of 1.
16. Run the iterations of the second inner loop with a parallel factor of 1.
#pragma ACCEL kernel

void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[60][70],double A[60][80],double B[80][70])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L3}
      for (j = 0; j < 70; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}