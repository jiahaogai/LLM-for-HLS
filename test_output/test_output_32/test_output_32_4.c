
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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L3}
      for (j = 0; j < 70; j++) {
        A[i][k]:
        C[i][j] += alpha * B[k][j] * A[i][k];
      }
    }
  }
}