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
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;
  int index;
  int last_row_idx;
  int last_a_idx;
  int last_b_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 52; a_idx++) {
    M[a_idx] = a_idx * (-1);
    ptr[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_col:
  for (b_idx = 0; b_idx < 52; b_idx++) {
    M[b_idx * 52] = b_idx * (-1);
    ptr[b_idx * 52] = ((char )0);
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 52; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 52; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = (b_idx - 1) * 52;
      row = b_idx * 52;
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] - 1;
      left = M[row + (a_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = ((char )'L');
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = ((char )'U');
        }
         else {
          ptr[row + a_idx] = ((char )'D');
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  index = 51 * 52 - 1;
  a_str_idx = 51;
  b_str_idx = 51;
  last_row_idx = (52 - 1) * 52;
  last_a_idx = 52 - 1;
  last_b_idx = 52 - 1;
  trace:
  while (a_str_idx > 0 || b_str_idx > 0) {
    r = M[index];
    if (ptr[index] == ((char )'L')) {
      a_idx = a_str_idx;
      b_idx = b_str_idx;
    }
     else {
      if (ptr[index] == ((char )'U')) {
        a_idx = last_a_idx;
        b_idx = b_str_idx;
      }
       else {
        a_idx = a_str_idx;
        b_idx = last_b_idx;
      }
    }
    alignedA[a_str_idx] = SEQA[a_idx];
    alignedB[b_str_idx] = SEQB[b_idx];
    a_str_idx--;
    b_str_idx--;
    last_row_idx = b_idx * 52;
    last_a_idx = a_idx;
    last_b_idx = b_idx;
    index = b_idx * 52 + a_idx;
  }
  alignedA[0] = '\0';
  alignedB[0] = '\0';
}