#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
<<<<<<< HEAD
// => A is N-by-N
//B is TRANSB = 'N'
// => B is N-by-M
// => therefore: M = 80
// =>               K = 60
// =>               N = 60
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{80}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
// => A is NIxNK
//B is NIxNJ
// => B is aligned by NI
// => PASSED AS NIx(NK*NJ)
// => LEAD TILE OF FACTOR NI
//TRANSAB = 'N'
// => Form B := alpha*A*B,
//A is TRANSA = 'T'
// => A is NKxNK
//B is NKxNJ
// => B is aligned by NK
// => PASSED AS (NK*NJ)xNK
// => LEAD TILE OF FACTOR NK
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (k = 0; k < 60; k++) {
        sum += alpha * A[k][i] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
<<<<<<< HEAD
  
#pragma endscop
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}