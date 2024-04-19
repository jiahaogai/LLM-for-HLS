#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;
  int a_str_idx_p1;
  int b_str_idx_p1;
  int a_str_idx_im1;
  int b_str_idx_im1;
  char a_char;
  char b_char;
  int score_u;
  int score_ul;
  int score_l;
  int mul;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      a_str_idx_im1 = (a_idx - 1);
      b_str_idx_im1 = (b_idx - 1);
      a_str_idx = a_idx;
      b_str_idx = b_idx;
      a_str_idx_p1 = (a_idx + 1);
      b_str_idx_p1 = (b_idx + 1);
      a_char = (SEQA[a_str_idx_im1]);
      b_char = (SEQB[b_str_idx_im1]);
      score_u = ((M[b_str_idx_im1 * (128 + 1)] > ((a_str_idx_im1) * - 1)) ? M[b_str_idx_im1 * (128 + 1)] : ((a_str_idx_im1) * - 1));
      score_ul = ((M[b_str_idx_p1 * (128 + 1) + a_str_idx_im1] > (score_u + 1)) ? M[b_str_idx_p1 * (128 + 1) + a_str_idx_im1] : (score_u + 1));
      score_l = ((M[b_str_idx_im1 * (128 + 1) + a_str_idx_p1] > ((b_str_idx_im1) * - 1)) ? M[b_str_idx_im1 * (128 + 1) + a_str_idx_p1] : ((b_str_idx_im1) * - 1));
      mul = (a_char == b_char) ? 1 : - 1;
      score = score_ul + mul;
      up_left = M[b_str_idx_p1 * (128 + 1) + a_str_idx_p1];
      up = M[b_str_idx_p1 * (128 + 1) + a_str_idx_im1];
      left = M[b_str_idx_im1 * (128 + 1) + a_str_idx_p1];
      u = up_left + ((a_char == 45) ? - 1 : ((b_char == 45) ? - 1 : ((mul - 1)));
      l = left + ((a_char == 45) ? - 1 : ((b_char == 45) ? - 1 : (mul)));
      max = (u > l) ? u : l;
      max = (score > max ? score : max);
      M[b_str_idx * (128 + 1) + a_str_idx] = max;
      if (max == score) {
        ptr[b_str_idx * (128 + 1) + a_str_idx] = 0;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (max == u) {
        if (up_left == up) {
          ptr[b_str_idx * (128 + 1) + a_str_idx] = 4;
        }
        else {
          ptr[b_str_idx * (128 + 1) + a_str_idx] = 2;
        }
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == l) {
        if (up_left == left) {
          ptr[b_str_idx * (128 + 1) + a_str_idx] = 8;
        }
        else {
          ptr[b_str_idx * (128 + 1) + a_str_idx] = 1;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 128;
  a_idx = 128 + 1;
  b_idx = 128 + 1;
  a_str_idx = 128;
  b_str_idx = 128;
/*
    trace: while(a_str_idx || b_str_idx) {
      row_up = b_str_idx - 1;
      a_str_idx_up = a_str_idx - 1;
      b_str_idx_up = b_str_idx - 1;
      mul = (SEQA[a_str_idx_up] == SEQB[b_str_idx_up]) ? 1 : - 1;
      score_u = (M[b_str_idx_up * (128 + 1)] > ((a_str_idx_up) * - 1)) ? M[b_str_idx_up * (128 + 1)] : ((a_str_idx_up) * - 1);
      score_ul = (M[b_str_idx_up * (128 + 1) + a_str_idx_up] > (score_u + mul)) ? M[b_str_idx