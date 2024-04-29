<<<<<<< HEAD
#pragma ACCEL kernel
=======
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
//A is NIxNK
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      for (i = 0; i < 80; i++) {
        sum += A[i][k] * B[i][j];
      }
      C[k][j] *= beta;
      C[k][j] += alpha * sum;
    }
  }
  
#pragma endscop
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
