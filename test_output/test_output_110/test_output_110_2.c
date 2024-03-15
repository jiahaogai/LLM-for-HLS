

7. For the inner loop, perform parallel reduction on variable "x" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1_2}`

8. For the outer loop, perform parallel reduction on variable "t" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=t FACTOR=auto{__PARA__L2}`

9. For the middle loop, perform parallel reduction on variable "u" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L3}`

10. For the middle loop, perform parallel reduction on variable "v" with the factor determined automatically:
   - Use: `#pragma ACCEL PARALLEL reduction=v FACTOR=auto{__PARA__L4}`

11. Mark the following function as a configuration function for kernel gemm:
   - Def: `void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220])`
   - ACCEL kernel
   - ACCEL PIPELINE auto{flatten}
   - ACCEL TILE FACTOR=auto{4}
   - ACCEL PARALLEL FACTOR=auto{1}
   
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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1_0}
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
