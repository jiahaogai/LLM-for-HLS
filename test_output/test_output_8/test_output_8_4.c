
 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <cutil_inline.h>
 
#define N 128
#define M 128
#define K 128
#define double float
// A is NxM
double A[N][M];
// B is MxK
double B[M][K];
// C is NxK
double C[N][K];
// Threads per block
#define BLOCK_SIZE 16
// Total number of threads
#define NUM_THREADS 256
 
double mul(double A,double B){
  return A * B;
}
 
void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[64][64],double A[64][64],double B[64][64])
{
  int i;
  int j;
  int k;
//#pragma scop
/* Standardize from: for(i = 0;i < 64;++i) {...} */
  
#pragma ACCEL PIPELINE auto{flatten}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      C[i][j] *= beta;
    }
  }
/* Standardize from: for(i = 0;i < 64;++i) {...} */
  
#pragma ACCEL PIPELINE auto{}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (k = 0; k < 64; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = 0; j < 64; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
/* Standardize from: for(i = 0;i < 64;++i) {...} */
  
#pragma ACCEL PIPELINE auto{off}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      C[i][j] += C[i][j];
    }
  }
//#pragma endscop
}
