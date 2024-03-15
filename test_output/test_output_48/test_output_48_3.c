
The application code is:
 #include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>
#include <omp.h>
#pragma ACCEL kernel

void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[60][70],double A[60][80],double B[80][70])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 70; j++) {
      C[i][j] *= beta;
    }
  }
  for (i = 0; i < 60; i++) {
    for (k = 0; k < 80; k++) {
      temp[i][k] = A[i][k] * alpha;
    }
  }
  for (i = 0; i < 60; i++) {
    for (j = 0; j < 70; j++) {
      C[i][j] += temp[i][0][0] * B[0][j];
    }
  }
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
//#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 60; i++) {
    for (j = 0; j < 70; j++) {
      double sum = (double )0;
      for (k = 0; k < 80; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
}
