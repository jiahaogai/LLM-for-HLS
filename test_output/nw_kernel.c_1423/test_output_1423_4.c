c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = 0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    score_loop:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = M[b_idx * 5] + gap_penalty;
      }
      else if (b_idx == 0) {
        M[b_idx + a_idx * 5] = M[a_idx + b_idx * 5] + gap_penalty;
      }
      else {
        up_left = M[(b_idx - 1) * 5 + (a_idx - 1)];
        up = M[b_idx * 5 + a_idx - 1] + gap_penalty;
        left = M[b_idx * 5 + a_idx - 1] + gap_penalty;
        if (up_left > left) {
          if (up_left > up) {
            max = up_left;
            ptr[b_idx * 5 + a_idx] = 2;
          }
          else {
            max = up;
            ptr[b_idx * 5 + a_idx] = 1;
          }
        }
        else {
          if (left > up) {
            max = left;
            ptr[b_idx * 5 + a_idx] = 3;
          }
          else {
            max = up;
            ptr[b_idx * 5 + a_idx] = 1;
          }
        }
        M[b_idx * 5 + a_idx] = SEQA[a_idx] == SEQB[b_idx] ? dp_match + max : dp_mismatch + max;
      }
    }
  }
  row = 5;
  b_str_idx = 5;
  a_str_idx = 0;
  r = ((5 + 1) * 5) - 1;
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  trace_reconstruct:
  while (a_idx != 0 || b_idx != 0) {
    if (ptr[b_idx * 5 + a_idx] == 0) {
      a_str_idx++;
      b_str_idx++;
      a_idx--;
      b_idx--;
    }
    else if (ptr[b_idx * 5 + a_idx] == 2) {
      a_str_idx++;
      b_str_idx--;
      a_idx--;
    }
    else if (ptr[b_idx * 5 + a_idx] == 3) {
      a_str_idx--;
      b_str_idx++;
      b_idx--;
    }
    else if (ptr[b_idx * 5 + a_idx] == 1) {
      a_str_idx--;
      b_str_idx--;
      a_idx--;
      b_idx--;
    }
  }
}