<<<<<<< HEAD
5. `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{8}`: This pragma directive executes the loop in parallel, reducing the variable `B`, with a factor of 8, meaning iterations are grouped and executed concurrently.

=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{8}

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A^T*B,
//A is TRANSA( A ) = A
//B is TRANSB( B ) = B
<<<<<<< HEAD
// => form B := alpha*A^T*B
=======
// => B := alpha*A^T*B = (alpha*A)^T*B
// => DIM(A) = (60.0, 60.0)
// => DIM(B) = (60.0, 80.0)
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{80}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{30}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[k][i] * B[k][j];
      }
    }
  }
  
#pragma endscop
}