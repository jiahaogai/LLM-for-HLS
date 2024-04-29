<<<<<<< HEAD
=======
- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}`:  Specify that the loop must be executed with reduction of the C variable.

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
<<<<<<< HEAD
// => Form C := alpha*A*B + beta*C,
=======
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
<<<<<<< HEAD
=======
#pragma scop
  
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
    for (j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
      for (k = 0; k < 60; k++) {
=======
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      for (j = 0; j < 80; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
=======
  
#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}