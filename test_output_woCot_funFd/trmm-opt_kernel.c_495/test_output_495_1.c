#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
// => Form B := alpha*A**T*B,
//A is M(60) x M(60)
//B is M(60) x N(80)
  
#pragma scop
=======
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{60}
<<<<<<< HEAD
      for (k = 0; k < 60; k++) {
=======
      for (k = 0; k < 60; ++k) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
  
#pragma endscop
=======
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}