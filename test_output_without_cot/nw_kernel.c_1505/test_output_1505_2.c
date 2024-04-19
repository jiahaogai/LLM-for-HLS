#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a > b) ? (b) : (a))

#define max(a, b) ((a > b) ? (a) : (b))

void needwun(char SEQA[128],
             char SEQB[128],
             char alignedA[256],
             char alignedB[256],
             int M[16641],
             char ptr[16641])
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
    int a_str_idx;
    int b_str_idx;
    int a_str_idx_p1;
    int b_str_idx_p1;
    int i;
    int j;
    int A_len_min_1;
    int B_len_min_1;
    char A_char;
    char B_char;
    A_len_min_1 = 127;
    B_len_min_1 = 127;
// Matrix initialization
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    init_row:
    for (a_idx = 0; a_idx < 128; a_idx++) {
        M[a_idx] = a_idx * - 1;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_col:
    for (b_idx = 0; b_idx < 128; b_idx++) {
        M[b_idx * 128] = b_idx * - 1;
    }
// Matrix filling
    
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_out:
    for (b_idx = 1; b_idx < 128; b_idx++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      fill_in:
      for (a_idx = 1; a_idx < 128; a_idx++) {
        if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
          score = 1;
        }
        else {
          score = - 1;
        }
        row_up = (b_idx - 1) * 128;
        up_left = row_up + (a_idx - 1);
        up = row_up + a_idx;
        left = up_left;
        max = M[up_left] + score;
        if (M[up] + - 1 > max) {
          max = M[up] + - 1;
          ptr[up] = 2;
        }
        if (max > M[left] + - 1) {
          M[up] = max;
          ptr[up] = left;
        }
        else {
          M[up] = M[left] + - 1;
          ptr[up] = left;
        }
        if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
          score = 1;
        }
        else {
          score = - 1;
        }
        row = b_idx * 128;
        a_str_idx_p1 = a_idx + 1;
        b_str_idx_p1 = b_idx + 1;
        a_str_idx = a_idx;
        b_str_idx = b_idx;
        if (a_str_idx_p1 == A_len_min_1) {
          A_char = - 1;
        }
        else {
          A_char = (SEQA)[a_str_idx_p1];
        }
        if (b_str_idx_p1 == B_len_min_1) {
          B_char = - 1;
        }
        else {
          B_char = (SEQB)[b_str_idx_p1];
        }
//#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (((int )A_char) == ((int )B_char)) {
          score = 1;
        }
        else {
          score = - 1;
        }
        if (M[row + a_str_idx] + score > M[row + a_str_idx] + - 1) {
          max = M[row + a_str_idx] + score;
          ptr[row + a_str_idx] = row + a_str_idx;
        }
        else {
          max = M[row + a_str_idx] + - 1;
          ptr[row + a_str_idx] = row + a_str_idx - 1;
        }
        if (M[row + a_str_idx] + - 1 > M[row + a_str_idx - 1] + score) {
          M[row + a_str_idx] = M[row + a_str_idx - 1] + score;
          ptr[row + a_str_idx] = row + a_str_idx - 1;
        }
        else {
          M[row + a_str_idx] = M[row + a_str_idx - 1] + - 1;
          ptr[row + a_str_idx] = row + a_str_idx - 1;
        }
        if (M[row + a_str_idx] > M[row + a_str_idx + 1] + score) {
          M[row + a_str_idx] = M[row + a_str_idx + 1] + score;
          ptr[row + a_str_idx] = row + a_str_idx + 1;
        }
        else {
          M[row + a_str_idx] = M[row + a_str_idx + 1] + score;
          ptr[row + a_str_idx] = row + a_str_idx + 1;
        }
      }
    }
// TraceBack
    i = 127;
    j = 127;
    a_str_idx = 127;
    b_str_idx = 127;
    track:
/* Standardize from: for( r = 127; r => 0;  ) */
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    trace:
    while (((int )A_char) != - 1) {
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      if (ptr[b_str_idx * 128 + a_str_idx] == b_str_idx * 128 + a_str_idx) {
        a_str_idx--;
        b_str_idx--;
        A_char = alignedA[a_str_idx];
        B_char = alignedB[b_str_idx];
      }
      else {
        if (ptr[b_str_idx * 128 + a_str_idx] == b_str_idx * 128 + a_str_idx + 1) {
          a_str_idx++;
          B_char = alignedB[b_str_idx];
          A_char = alignedA[a_str_idx];
        }
        else {