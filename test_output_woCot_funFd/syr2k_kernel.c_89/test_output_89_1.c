<<<<<<< HEAD
- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Execute the most outer loop iterations concurrently with a factor of 2, potentially improving parallelism.
=======
- `#pragma ACCEL PARALLEL FACTOR=auto{4}`: Execute the most outer loop iterations concurrently with a factor of 4, potentially improving parallelism.
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

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
<<<<<<< HEAD
//B is NKxNJ
//C is NIxNJ
=======
//B is NIxNK
//C is NKxNK
  
#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{5}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
=======
  
#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}