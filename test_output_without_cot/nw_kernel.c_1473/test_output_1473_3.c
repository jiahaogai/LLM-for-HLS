#include <stdio.h>
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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      up_left = M[(b_idx - 1) * (128 + 1) + (a_idx - 1)] + score;
      up = M[(b_idx - 1) * (128 + 1) + a_idx] - 1;
      left = M[b_idx * (128 + 1) + (a_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      row_up = (b_idx - 1) * (128 + 1);
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = ((char )60);
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = ((char )94);
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = ((char )92);
          b_str_idx = ((b_idx + ((int )ptr[row_up * (128 + 1) + a_idx])) - 1);
          a_str_idx = ((a_idx + ((int )ptr[row_up * (128 + 1) + a_idx + 1])) - 1);
          if (a_str_idx < 0) {
            a_str_idx = 0;
          }
          if (b_str_idx < 0) {
            b_str_idx = 0;
          }
          if (a_str_idx >= 128 + 1) {
            a_str_idx = 128;
          }
          if (b_str_idx >= 128 + 1) {
            b_str_idx = 128;
          }
          ptr[b_idx * (128 + 1) + a_idx] = ((char )((int )ptr[b_idx * (128 + 1) + a_idx]) + (int )ptr[row_up * (128 + 1) + a_idx]);
          ptr[b_idx * (128 + 1) + a_idx] = ((char )(ptr[b_idx * (128 + 1) + a_idx] + a_str_idx));
          ptr[b_idx * (128 + 1) + a_idx] = ((char )(ptr[b_idx * (128 + 1) + a_idx] + b_str_idx));
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 128;
  b_idx = 128;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    trace: while(a_idx>0 || b_idx>0) {
      r = b_idx*(ALEN+1);
      row = r + a_idx;
      if (ptr[row] == ALIGN){
        alignedA[a_str_idx++] = SEQA[a_idx-1];
        alignedB[b_str_idx++] = SEQB[b_idx-1];
        a_idx--;
        b_idx--;
      }
      else if (ptr[row] == SKIPB){
        alignedA[a_str_idx++] = SEQA[a_idx-1];
        alignedB[b_str_idx++] = '-';
        a_idx--;
      }
      else{ // SKIPA
        alignedA[a_str_idx++] = '-';
        alignedB[b_str_idx++] = SEQB[b_idx-1];
        b_idx--;
      }
    }
    // Pad the result
    pad_a: for( ; a_str_idx<ALEN+BLEN; a_str_idx++ ) {
      alignedA[a_str_idx] = '_';
    }
    pad_b: for( ; b_str_idx<ALEN+BLEN; b_str_idx++ ) {
      alignedB[b_str_idx] = '_';
    }
*/
}