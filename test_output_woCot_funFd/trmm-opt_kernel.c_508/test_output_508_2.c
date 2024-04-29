<<<<<<< HEAD
Code: ### Function Header:
 #pragma ACCEL kernel
=======
Code: ### Generated from:
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

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
//A is TRANSA = 'T'
// => A is N-BY-N
//B is TRANSB = 'N'
// => B is N-BY-80
// => => product is N-BY-80
=======
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      B[i][j] *= alpha;
=======
#pragma ACCEL PARALLEL reduction = A FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[k][i] * B[k][j];
      }
    }
  }
=======
#pragma ACCEL PARALLEL reduction = B FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}