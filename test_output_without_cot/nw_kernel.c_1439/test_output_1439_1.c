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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      a_str_idx = a_idx * 16;
      b_str_idx = b_idx * 16;
      score = ((int )SEQA[a_str_idx + 0]) * ((int )SEQB[b_str_idx + 0]) + ((int )SEQA[a_str_idx + 1]) * ((int )SEQB[b_str_idx + 1]) + ((int )SEQA[a_str_idx + 2]) * ((int )SEQB[b_str_idx + 2]) + ((int )SEQA[a_str_idx + 3]) * ((int )SEQB[b_str_idx + 3]) + ((int )SEQA[a_str_idx + 4]) * ((int )SEQB[b_str_idx + 4]) + ((int )SEQA[a_str_idx + 5]) * ((int )SEQB[b_str_idx + 5]) + ((int )SEQA[a_str_idx + 6]) * ((int )SEQB[b_str_idx + 6]) + ((int )SEQA[a_str_idx + 7]) * ((int )SEQB[b_str_idx + 7]) + ((int )SEQA[a_str_idx + 8]) * ((int )SEQB[b_str_idx + 8]) + ((int )SEQA[a_str_idx + 9]) * ((int )SEQB[b_str_idx + 9]) + ((int )SEQA[a_str_idx + 10]) * ((int )SEQB[b_str_idx + 10]) + ((int )SEQA[a_str_idx + 11]) * ((int )SEQB[b_str_idx + 11]) + ((int )SEQA[a_str_idx + 12]) * ((int )SEQB[b_str_idx + 12]) + ((int )SEQA[a_str_idx + 13]) * ((int )SEQB[b_str_idx + 13]) + ((int )SEQA[a_str_idx + 14]) * ((int )SEQB[b_str_idx + 14]) + ((int )SEQA[a_str_idx + 15]) * ((int )SEQB[b_str_idx + 15]);
      up_left = M[(b_idx - 1) * 64 + (a_idx - 1)] + ((int )SEQA[a_str_idx + 15]) * ((int )SEQB[b_str_idx + 15]);
      up = M[b_idx * 64 + a_idx - 1] + ((int )SEQA[a_str_idx + 15]) - ((int )SEQB[b_str_idx + 15]);
      left = M[(b_idx - 1) * 64 + a_idx] + ((int )SEQB[b_str_idx + 15]) - ((int )SEQA[a_str_idx + 15]);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * 64 + a_idx] = max;
      row_up = b_idx * 64 + a_idx - 1;
      if (max == left) {
        ptr[b_idx * 64 + a_idx] = ((char )60);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      trace:
      for (r = 0; r < 16; r++) {
        row = (b_idx * 16) + r;
        if (row_up == row) {
          b_str_idx = b_idx * 16 + 15;
          a_str_idx = (a_idx - 1) * 16 + r;
          break;
        }
      }
    }
  }
// Traceback
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  trace_out:
  for (b_idx = 55; b_idx >= 0; b_idx--) {
    trace_in:
    for (a_idx = 55; a_idx >= 0; a_idx--) {
      a_str_idx = a_idx * 16;
      b_str_idx = b_idx * 16;
      score = ((int )SEQA[a_str_idx + 0]) * ((int )SEQB[b_str_idx + 0]) + ((int )SEQA[a_str_idx + 1]) * ((int )SEQB[b_str_idx + 1]) + ((int )SEQA[a_str_idx + 2]) * ((int )SEQB[b_str_idx + 2]) + ((int )SEQA[a_str_idx + 3]) * ((int )SEQB[b_str_idx + 3]) + ((int )SEQA[a_str_idx + 4]) * ((int )SEQB[b_str_idx + 4]) + ((int )SEQA[a_str_idx + 5]) * ((int )SEQB[b_str_idx + 5]) + ((int )SEQA[a_str_idx + 6]) * ((int )SEQB[b_str_idx + 6]) + ((int )SEQA[a_str_idx + 7]) * ((int )SEQB[b_str_idx + 7]) + ((int )SEQA[a_str_idx + 8]) * ((int )SEQB[b_str_idx + 8]) + ((int )SEQA[a_str_idx + 9]) * ((int )SEQB[b_str_idx + 9]) + ((int )SEQA[a_str_idx + 10]) * ((int )SEQB[b