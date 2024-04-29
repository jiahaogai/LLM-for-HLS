- The middle loop is not automatically pipelined to maximize performance.
- The middle loop is kept whole without division into smaller parts to maintain data locality.
- Loop iterations of the middle loop are executed sequentially, ensuring correct dependencies are observed.
- The middle loop is automatically unrolled by a factor of 2.
- The inner loop of the middle loop is not automatically pipelined to maximize performance.
- The inner loop of the middle loop is kept whole without division into smaller parts to maintain data locality.
- Loop iterations of the inner loop of the middle loop are executed sequentially, ensuring correct dependencies are observed.
- The inner loop is not automatically pipelined to maximize performance.
- The inner loop is kept whole without division into smaller parts to maintain data locality.
- Loop iterations of the inner loop are executed sequentially, ensuring correct dependencies are observed.
- The flatten pragma is used to control code generation for the inner loop.
- Tile FACTOR=auto{8} is used to control code generation for the inner loop.
- PIPELINE auto{off} is used to control code generation for the inner loop.
- The parallelization factor of 1 is used to control code generation for the inner loop.

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + beta*C,
//A is ROWMAJOR
//B is ROWMAJOR
//C is ROWMAJOR
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{70}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}