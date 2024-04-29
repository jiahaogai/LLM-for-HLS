Code: #pragma ACCEL PIPELINE auto{off}`: Disables loop pipelining in order to avoid excess buffering and allow smaller buffers to be used.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keeps the loop whole without dividing it into smaller parts, with a tile factor of 1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Executes loop iterations sequentially, not concurrently, with a parallel factor of 1.

### 

 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form C := alpha*A**T*B + alpha*B**T*A + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[k][i] * B[k][j];
      }
    }
  }
  
#pragma endscop
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}`: Disables loop pipelining in order to avoid excess buffering and allow smaller buffers to be used.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keeps the loop whole without dividing it into smaller parts, with a tile factor of 1.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Executes loop iterations sequentially, not concurrently, with a parallel factor of 1.

### 

 #pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'T'
// => Form C := alpha*A**T*B**T + alpha*B**T*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLE