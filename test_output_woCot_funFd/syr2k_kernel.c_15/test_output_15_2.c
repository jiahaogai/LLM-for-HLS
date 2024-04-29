<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}` - Do not pipeline the loop iterations.
  - `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the loop whole, without dividing it into smaller parts.
  - `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations sequentially, not concurrently, with a factor of 1.

#pragma ACCEL kernel
 
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
 
#pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
 #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{8}
=======
#pragma ACCEL TILE FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
//#pragma endscop
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}