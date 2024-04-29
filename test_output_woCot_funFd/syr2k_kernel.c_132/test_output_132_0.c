<<<<<<< HEAD
=======
#ifndef _KERNEL_SYR2K_H_
#define _KERNEL_SYR2K_H_
/******************************************************************/
/* Header file for kernel_syr2k                                    */
/******************************************************************/
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
// => Form C := alpha*A*B**T + beta*C,
//A is ROW MAJOR
//B is ROW MAJOR
//C is ROW MAJOR
=======
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{32}
=======
#pragma ACCEL PARALLEL FACTOR=auto{4}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
=======
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
<<<<<<< HEAD
}
=======
}
#endif
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
