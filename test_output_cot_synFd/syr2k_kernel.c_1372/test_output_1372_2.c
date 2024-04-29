Code: #pragma ACCEL PIPELINE auto{off}` (inner loop):
  - Explanation: Do not automatically pipeline this loop. This pragma disables automatic pipelining for the loop following it.

- `#pragma ACCEL TILE FACTOR=auto{1}` (inner loop):
  - Explanation: Keep this loop whole, without dividing it into smaller parts. This pragma sets the tile factor to 1 for the inner loop, meaning the loop should not be tiled into smaller sub-loops.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}` (inner loop):
  - Explanation: Execute loop iterations sequentially, not concurrently. This pragma sets the parallel factor to 1 for the inner loop, meaning loop iterations should be executed sequentially.

- `#pragma ACCEL PIPELINE auto{}`:
  - Explanation: Automatically pipeline this loop. This pragma enables automatic pipelining for the loop following it.

- `#pragma ACCEL TILE FACTOR=auto{1}` (inner loop):
  - Explanation: Keep this loop whole, without dividing it into smaller parts. This pragma sets the tile factor to 1 for the inner loop, meaning the loop should not be tiled into smaller sub-loops.

- `#pragma ACCEL PARALLEL FACTOR=auto{2}` (inner loop):
  - Explanation: Execute loop iterations concurrently with a parallel factor of 2. This pragma sets the parallel factor to 2 for the inner loop, meaning loop iterations can be executed concurrently with a factor of 2.

### Code:
 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{10}
      for (j = 0; j < 60; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}