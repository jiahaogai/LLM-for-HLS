
**seq.c**

 #include <stdio.h> 
 #include <sys/time.h>
#include <math.h>
#include <stdlib.h>
																				
#define N 120
																				
double A[N][N];
double B[N][N];
double C[N][N];
																				
void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[60][60],double A[60][60],double B[60][60])
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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (j = 0; j < 60; j++) {
      C[i][j] *= beta;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 0; j < 60; j++) {
      double temp = A[i][0] * B[0][j];
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (k = 1; k < 30; k++) {
        temp += A[i][k] * B[k][j];
      }
      C[i][j] += temp;
    }
  }
}
 
int main()
{
  int i;
  int j;
  int ki;
  int kj;
  double alpha = (double )1.8;
  double beta = (double )0.9;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (j = 0; j < 60; j++) {
      C[i][j] = 0.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 60; j++) {
      A[i][j] = 0.0;
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 0; j < 60; j++) {
      B[i][j] = 0.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    for (j = 0; j < 60; j++) {
      for (ki = 0; ki < 30; ki++) {
        A[i][j] += alpha * B[ki][j] * A[ki][j];
      }
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    for (j = 0; j < 60; j++) {
      C[i][j] += A[i][j];
    }
  }
/* End Do