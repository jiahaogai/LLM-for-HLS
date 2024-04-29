- `#pragma ACCEL TILE FACTOR=auto{4}`: Divide the loop into tiles of size 4 to exploit data reuse and prevent excessive resource consumption.

- `#pragma ACCEL PIPELINE auto{off}`: Do not pipeline the loop.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Divide the loop into tiles of size 1 to exploit data reuse and prevent excessive resource consumption.

- `#pragma ACCEL PARALLEL FACTOR=auto{5}`: Execute loop iterations concurrently to achieve parallelism.

- `#pragma ACCEL PIPELINE auto{off}`: Do not pipeline the loop.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Divide the loop into tiles of size 1 to exploit data reuse and prevent excessive resource consumption.

- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently to achieve parallelism.

- `#pragma ACCEL PIPELINE auto{off}`: Do not pipeline the loop.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Divide the loop into tiles of size 1 to exploit data reuse and prevent excessive resource consumption.

- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute loop iterations concurrently to achieve parallelism.

- `#pragma ACCEL PIPELINE auto{off}`: Do not pipeline the loop.

- `#pragma ACCEL TILE FACTOR=auto{1}`: Divide the loop into tiles of size 1 to exploit data reuse and prevent excessive resource consumption.

- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute loop iterations concurrently to achieve parallelism.

#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNJ
//K is NK
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{5}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}