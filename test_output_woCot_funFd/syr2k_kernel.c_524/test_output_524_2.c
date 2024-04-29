#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
<<<<<<< HEAD
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NIxNK
//C is NKxNK
=======
// => Form C := alpha*A*A**T + beta*C,
//A => A[80][60]
//B => B[80][60]
//C => C[80][80]
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{10}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma endscop
}