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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = 0;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = ((int )5) * a_idx;
      b_str_idx = ((int )5) * b_idx;
      up_left = M[(a_idx - 1) * 5 + (b_idx - 1)];
      up = M[(a_idx - 1) * 5 + b_idx];
      left = M[a_idx * 5 + (b_idx - 1)];
      score = ((SEQA[a_str_idx + 5 - 1] == SEQB[b_str_idx + 5 - 1]) ? 1 :  - 1);
      max = (up_left + score);
      max = (up + ((int )1)) > max ? (up + ((int )1)) : max;
      max = left > max ? left : max;
      M[a_str_idx + b_str_idx] = max;
      row_up = ((a_idx - 1) * 5) + b_idx;
      if (max == up_left + score) {
        ptr[a_str_idx + b_str_idx] = 15;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      fill_diag:
      for (r = 0; r < 5 - 1; r++) {
        row = r * 5;
        row_up = (r + 1) * 5;
        up = M[row_up + a_idx];
        up_left = M[row_up + (a_idx - 1)];
        left = M[row + b_idx];
        score = ((SEQA[a_str_idx + r + 5 - 1] == SEQB[b_str_idx + r + 5 - 1]) ? 1 :  - 1);
        max = (up_left + score);
        max = (up + ((int )1)) > max ? (up + ((int )1)) : max;
        max = left > max ? left : max;
        M[a_str_idx + b_str_idx + r + 1] = max;
        if (max == up_left + score) {
          ptr[a_str_idx + b_str_idx + r + 1] = 4;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 4;
  b_idx = 4;
  a_str_idx = (((int )5) * 4) + 4;
  b_str_idx = (((int )5) * 4) + 4;
/*
    traceBack: while(a_idx != 0 || b_idx != 0) {
      row_up = ((a_idx - 1) * 5) + b_idx;
      up = M[row_up];
      row = a_idx * 5 + b_idx;
      left = M[row];
      up_left = M[row_up - 1];
      if (left > up && left > up_left) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_str_idx];
        alignedB[b_str_idx] = SEQB[b_str_idx];
        b_str_idx = b_str_idx - 1;
        a_str_idx = a_str_idx - 1;
      }
      else if (up > up_left) {
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_str_idx];
        alignedB[b_str_idx] = '_';
        a_str_idx = a_str_idx - 1;
      }
      else {
        a_idx = a_idx - 1;
        alignedA[a_str_idx] = '_';
        alignedB[b_str_idx] = SEQB[b_str_idx];
        b_str_idx = b_str_idx - 1;
      }
    }
  }
*/
}