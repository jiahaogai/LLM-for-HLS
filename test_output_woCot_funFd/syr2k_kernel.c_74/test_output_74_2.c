<<<<<<< HEAD
- The `C`, `A`, and `B` arguments are defined as `restrict` in the C99 standard. This means that the CPU and DSP hardware are allowed to reuse the same memory location for different accesses, but only if the accesses are non-overlapping. This allows for more efficient memory storage and processing.
=======
- The `A`, `B`, `C` arguments are passed by reference to this function. In other words, the function can modify the data pointed to by the arguments. Because `kernel_syr2k` receives pointers to the storage for `A`, `B`, and `C`, the `kernel_syr2k` function is said to be an _inplace_ function with respect to the arguments.
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
//B is NIxNK
//C is NKxNK
  
#pragma scop
  
=======
//B is NKxNJ
//C is NKxNK
  
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{4}
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
=======
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 60; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
  
#pragma endscop
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}