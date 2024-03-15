
- Flatten the following loop nest: 'Flatten the following loop nest'
- Parallelize the following loop nest: 'Parallelize this loop with 4096 threads'
- Distribute the following loop nest across 256 processors: 'Distribute this kernel to 256 processes'
- Use the following number of threads: 'Set the number of threads to 4096'
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
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 80; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 0; j < 70; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}
