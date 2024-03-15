  
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  
  
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
  
#include "gemm.h"
  
double time_gemm(double A[4096],double B[4096],double C[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 64; j++) {
      i_col = i * 64;
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{12}
      inner:
      for (k = 0; k < 64; k++) {
        k_col = k * 64;
        mult = A[i_col + k] * B[k_col + j];
        sum += mult;
      }
      C[i_col + j] = sum;
    }
  }
}
  
void gemm(double A[4096],double B[4096],double C[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 64; j++) {
      i_col = i * 64;
      sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{12}
      inner:
      for (k = 0; k < 64; k++) {
        k_col = k * 64;
        mult = A[i_col + k] * B[k_col + j];
        sum += mult;
      }
      C[i_col + j] = sum;
    }
  }
}
