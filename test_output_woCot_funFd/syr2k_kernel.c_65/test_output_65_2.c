<<<<<<< HEAD
=======
- `#pragma ACCEL PARALLEL FACTOR=auto{5}`: Limits the total number of loop iterations to 5, which is appropriate for this function.

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
//C is NIxNJ
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
<<<<<<< HEAD
      for (j = 0; j < 80; j++) {
=======
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