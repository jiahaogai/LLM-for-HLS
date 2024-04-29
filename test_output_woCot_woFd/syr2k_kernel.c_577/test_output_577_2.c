- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}`: For each iteration of the inner loop, C is multiplied by a factor of 8.
- `#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}`: For each iteration of the middle loop, A is multiplied by a factor of 1.
- `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}`: For each iteration of the middle loop, B is multiplied by a factor of 1.


### SEQUENTIAL

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
//B is NIxNK
//C is NKxNK
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{60}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] *= beta;
    }
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      B[i][j] *= beta;
    }
  }
}