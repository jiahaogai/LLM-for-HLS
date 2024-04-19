#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],char ptr[1664],int m,int n,int alen)
{
  int i;
  int j;
  int p;
  int q;
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (i = 0; i < 5; i++) {
    M[i] = i * - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (i = 0; i < 5; i++) {
    M[i * 64] = i * - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_a:
  for (a_idx = 1; a_idx < 64 - 1; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_b:
    for (b_idx = 1; b_idx < 64 - 1; b_idx++) {
      score = ((SEQA[a_idx * 8 + 0] == SEQB[b_idx * 8 + 0]) ? 1 : 0) + ((SEQA[a_idx * 8 + 1] == SEQB[b_idx * 8 + 1]) ? 1 : 0) + ((SEQA[a_idx * 8 + 2] == SEQB[b_idx * 8 + 2]) ? 1 : 0) + ((SEQA[a_idx * 8 + 3] == SEQB[b_idx * 8 + 3]) ? 1 : 0) + ((SEQA[a_idx * 8 + 4] == SEQB[b_idx * 8 + 4]) ? 1 : 0) + ((SEQA[a_idx * 8 + 5] == SEQB[b_idx * 8 + 5]) ? 1 : 0) + ((SEQA[a_idx * 8 + 6] == SEQB[b_idx * 8 + 6]) ? 1 : 0) + ((SEQA[a_idx * 8 + 7] == SEQB[b_idx * 8 + 7]) ? 1 : 0);
      up_left = M[(a_idx - 1) * 64 + (b_idx - 1)] + ((SEQA[a_idx * 8 + 0] == SEQB[b_idx * 8 + 0]) ? 1 : 0);
      up = M[(a_idx - 1) * 64 + b_idx] - 1;
      left = M[a_idx * 64 + (b_idx - 1)] - 1;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[a_idx * 64 + b_idx] = max;
      if (max == left) {
        ptr[a_idx * 64 + b_idx] = 2;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_c:
      for (p = a_idx * 8 + 1; p < ((a_idx * 8 + 1) + 7); p++) {
        row_up = p * 64 + (b_idx - 1);
        row = p * 64 + b_idx;
        up_left = M[row_up] + ((SEQA[p] == SEQB[b_idx * 8 + 0]) ? 1 : 0) - ((SEQA[p] == SEQB[b_idx * 8 + 7]) ? 1 : 0);
        up = M[row_up] - 1;
        left = M[row] - 1;
        max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
        M[row] = max;
        if (max == left) {
          ptr[row] = 1;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
        loop_d:
        for (q = b_idx * 8 + 1; q < ((b_idx * 8 + 1) + 7); q++) {
          score = M[p * 64 + q] + ((SEQA[p] == SEQB[q]) ? 1 : 0);
          up_left = M[(p - 1) * 64 + (q - 1)] + ((SEQA[p] == SEQB[q]) ? 1 : 0) - score;
          up = M[(p - 1) * 64 + q] - 1;
          left = M[p * 64 + (q - 1)] - 1;
          max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
          M[p * 64 + q] = max;
          if (max == left) {
            ptr[p * 64 + q] = 3;
          }
        }
      }
    }
  }
// TraceBack
  i = 63;
  j = 63;
  r = 0;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 0];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 1];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 2];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 3];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 4];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 5];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 6];
  r++;
  alignedA[r] = SEQA[i * 8 + 0];
  alignedB[r] = SEQB[j * 8 + 7];
  r++;
  loop_e:
  for (p = i * 8 + 1; p < ((i * 8 + 1) + 7); p++) {
    if (ptr[p * 64 + j] == 1) {
      up = p * 64 + j;
      alignedA[r] = SEQA[p];
      alignedB[r] = SEQB[up];
      r++;
      alignedA[r] =