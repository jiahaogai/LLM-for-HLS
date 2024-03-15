

 *
 * File loop_row.c: 
 * 
 * Code based on previous loop_row.c version, Apr 14 2006 10:04:51
 * 
 * 
 * 
 * PARAMS:
 *  I = 240 
 *  J = 280 
 *  TMP = 240 
 *  N = 40 
 *  NC = 40 
 *  NR = 20 
 *  NQ = 240 
 *  PQ = 16 
 *  P = 2 
 *  Q = 2 
 */
 #include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "../benchmarks.h"

#include "bench_main.h"


double kernel_doitgen(double A[240][280], double C4[40][40], double sum[40])
{
  int i;
  int p;
  int q;
  int j;
  int p_col;
  int q_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_p:
  for (i = 0; i < 240; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loop_q:
    for (j = 0; j < 280; j++) {
      sum[i] = 0.0;
      loop_p_col:
      for (p = 0; p < 20; p++) {
        p_col = i * 20 + p;
        loop_q_col:
        for (q = 0; q < 240; q++) {
          q_col = j * 240 + q;
          mult = A[p_col][q_col] * A[q_col][j];
          sum[i] = sum[i] + mult;
        }
      }
      A[i][j] = sum[i] + C4[i][j];
    }
  }
}


double kernel_dotprod(double A[240][280], double B[240][280], double C[240][280])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 240; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loop_j:
    for (j = 0; j < 280; j++) {
      i_col = i * 240;
      sum = 0.0;
      loop_k:
      for (k = 0; k < 20; k++) {
        k_col = i * 20 + k;
        mult = A[k_col][j] * B[i_col + k];
        sum = sum + mult;
      }
      C[i_col + j] = sum;
    }
  }
}


double kernel_triad(double A[240][280], double B[240][280], double C[240][280])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult_1;
  double mult_2;
  double add;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 240; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    loop_j:
    for (j = 0; j < 280; j++) {
      i_col = i * 240;
      loop_k:
      for (k = 0; k < 20; k++) {
        k_col = i * 20 + k;
        mult_1 = B[k_col][j] * A[k_col][j];
        loop_k_col:
        for (k_col = i * 20; k_col < (i * 20 + 20); k_col++) {
          mult_2 = B[i_col + k][k_col] * A[k_col][j];
          add = mult_1 + mult_2;
          C[i_col + k_col] = C[i_col + k_col] + add;
        }
      }
    }
  }
}


int main(int argc,char **argv) {
  double A[240][280];
  double B[240][280];
  double C[240][280];
  double D[240][280];
  double C4[40][40];
  double sum[40];
  double rA[20][240][280];
  double rB[20][240][280];
  double rC[20][40][280];
  double rD[20][240][280];
  double res[40][240][280];
  double tmp[40][280];
  double tmp_1[240][280];
  double tmp_2[240][280];
  double tmp_3[40][280];
  double res_1[40][240][280];
  double exp[40][240][280];
  double check[40][240][280];
  double e;
  int i;
  int j;
  int k;
  
#pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_kernel:
  for (i = 0; i < 240; i++) {
    init_kernel_0:
    for (j = 0; j < 280; j++) {
      A[i][j] = (double )0;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  init_kernel_1:
  for (i = 0; i < 240; i++) {
    init_kernel_2:
    for (j = 0; j < 280; j++) {
      B[i][j] = (double )0;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  init_kernel_3:
  for (i = 0; i < 240; i++) {
    init_kernel_4:
    for (j = 0; j < 280; j++) {
      C[i][j] = (double )0;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  init_kernel_