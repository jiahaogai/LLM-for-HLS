
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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
  }
  for (i = 0; i < 60; i++) {
    for (k = 0; k < 80; k++) {
      temp[i][k] = A[i][k] * beta;
    }
    for (j = 0; j < 70; j++) {
      for (k = 0; k < 80; k++) {
        C[i][j] += alpha * temp[i][k] * B[k][j];
      }
    }
  }
}