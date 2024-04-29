#pragma ACCEL kernel

void kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'T'
//TRANSB = 'N'
<<<<<<< HEAD
// => Form B := alpha*A'*B,
//A' is A(60-1 : 60-1)
//B is B(60-1 : 80-1)
// => Product is B(60-1 : 80-1)
=======
// => Form B := alpha*A**T*B,
//A is TRANSA = 'T'
//B is TRANSB = 'N'
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
#pragma ACCEL PARALLEL FACTOR=auto{4}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{80}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 60; k++) {
        sum += alpha * A[k][i] * B[k][j];
      }
      B[i][j] = sum;
    }
  }
  
#pragma endscop
}