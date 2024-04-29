- The ACCEL runtime, after compiling an application that contains the `#pragma ACCEL kernel` function, will instantiate the kernel function once on application startup. After instantiation, the kernel will be available for execution and will continue to be available for execution until the application is terminated.

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
//A is ROW MAJOR
//B is ROW MAJOR
//C is ROW MAJOR
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}