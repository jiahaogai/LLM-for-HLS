#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
 
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
 
#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[160],char alignedB[160],char ptr[129])
{
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
  int a_idx_up;
  int b_idx_up;
  int a_str_idx;
  int b_str_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    ptr[a_idx] = a_idx;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    ptr[128 + b_idx] = b_idx;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  score_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    score_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_idx_up = 1 + a_idx;
      b_idx_up = 1 + b_idx;
      a_str_idx = a_idx * 16;
      b_str_idx = b_idx * 16;
      up_left = ((int )alignedA[a_idx_up - 1]) * ((int )alignedB[b_idx_up - 1]);
      up = ((int )alignedA[a_idx_up - 1]) * ((int )alignedB[b_idx]);
      left = ((int )alignedA[a_idx]) * ((int )alignedB[b_idx_up - 1]);
      max = ((int )alignedA[a_idx_up - 1]) + ((int )alignedB[b_idx_up - 1]);
      if (left > ((int )alignedA[a_idx]) + ((int )alignedB[b_idx])) {
        max = left;
        row = a_idx_up;
        r = b_idx_up;
      }
      else {
        max = ((int )alignedA[a_idx]) + ((int )alignedB[b_idx]);
        row = a_idx;
        r = b_idx;
      }
      if (up_left > max) {
        max = up_left;
        row = a_idx_up;
        r = b_idx_up;
      }
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      score = ((int )alignedA[a_idx]) + ((int )alignedB[b_idx]);
      if (score > up) {
        score = up;
      }
      if (score > left) {
        score = left;
      }
      if (score > up_left) {
        score = up_left;
        row = a_idx_up;
        r = b_idx_up;
      }
      M[a_idx][b_idx] = score;
    }
  }
  row_up = 1;
  r_up = 1;
  a_idx = 5;
  b_idx = 5;
  a_str_idx = 112;
  b_str_idx = 16;
/* TraceBack */
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  trace:
  while (1) {
    if (a_idx > 0 && b_idx > 0) {
      if (M[a_idx][b_idx] == M[a_idx - 1][b_idx - 1] + ((int )alignedA[a_idx] == (int )alignedB[b_idx])) {
        up_left = 0;
      }
      else {
        up_left = 1;
      }
      if (M[a_idx][b_idx] == M[a_idx - 1][b_idx] + ((int )alignedA[a_idx])) {
        up = 2;
      }
      else {
        up = 3;
      }
      if (M[a_idx][b_idx] == M[a_idx][b_idx - 1] + ((int )alignedB[b_idx])) {
        left = 4;
      }
      else {
        left = 5;
      }
      if (M[a_idx][b_idx] > M[a_idx - 1][b_idx - 1] + ((int )alignedA[a_idx] == (int )alignedB[b_idx])) {
        max = M[a_idx - 1][b_idx - 1];
        row = a_idx_up;
        r = b_idx_up;
      }
      else {
        max = M[a_idx][b_idx];
        row = a_idx;
        r = b_idx;
      }
      if (M[a_idx][b_idx] > M[a_idx - 1][b_idx] + ((int )alignedA[a_idx])) {
        max = M[a_idx - 1][b_idx];
        row = a_idx_up;
        r = b_idx;
      }
      if (M[a_idx][b_idx] > M[a_idx][b_idx - 1] + ((int )alignedB[b_idx])) {
        max = M[a_idx][b_idx - 1];
        row = a_idx;
        r = b_idx_up;
      }
    }
    else {
      if (a_idx == 0 && b_idx > 0) {
        up_left = 1;
        up = 3;
        left = 4;
        max = M[a_idx][b_idx - 1] + ((int )alignedB[b_idx]);
        row = a_idx;
        r = b_idx_up;
      }
      else {
        if (a_idx > 0 && b_idx == 0) {
          up_left = 1;
          up = 2;
          left = 5;
          max = M[a_idx - 1][b_idx] + ((int )alignedA[a_idx]);
          row = a_idx_up;
          r = b_idx;
        }
        else {
          up_left = 0;
          up = 3;
          left = 5;
          max = ((int )alignedA[a_idx]) + ((int )alignedB[b_idx]);
          row = a_idx_up;
          r = b_idx;
        }