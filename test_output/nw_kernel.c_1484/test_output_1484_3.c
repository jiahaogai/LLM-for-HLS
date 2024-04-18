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
  int a_str_idx_p1;
  int b_str_idx_p1;
  int a_str_idx_p2;
  int b_str_idx_p2;
  int idx_row;
  int idx_row_up;
  char a_char;
  char b_char;
  char pad = '_';
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = 3;
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = 1;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 128;
  b_idx = 128 + 1;
  a_idx = 128 + 1;
  a_str_idx = 0;
  b_str_idx = 0;
  a_str_idx_p1 = 0;
  b_str_idx_p1 = 0;
  a_str_idx_p2 = 0;
  b_str_idx_p2 = 0;
/* Pad A */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_a:
  while (a_str_idx < 256) {
    alignedA[a_str_idx] = pad;
    a_str_idx_p1 = a_str_idx + 1;
    a_str_idx ++;
  }
/* Pad B */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_b:
  while (b_str_idx < 256) {
    alignedB[b_str_idx] = pad;
    b_str_idx_p1 = b_str_idx + 1;
    b_str_idx ++;
  }
  idx_row = ((b_idx - 1) * (128 + 1));
  idx_row_up = ((b_idx - 1) * (128 + 1));
  a_str_idx = a_str_idx_p2;
  b_str_idx = b_str_idx_p2;
  trace_row:
  while (b_idx > 0) {
    a_str_idx_p2 = a_str_idx;
    b_str_idx_p2 = b_str_idx;
    row_up = idx_row_up;
    row = idx_row;
    a_str_idx = a_str_idx_p1;
    b_str_idx = b_str_idx_p1;
    idx_row_up = row_up + (128 + 1);
    idx_row = row + (128 + 1);
    trace_col:
    while (a_idx > 0) {
      a_str_idx_p1 = a_str_idx;
      b_str_idx_p1 = b_str_idx;
      if (ptr[b_str_idx * (128 + 1) + a_str_idx] == 2) {
        a_char = pad;
        b_char = pad;
      }
       else {
        if (ptr[b_str_idx * (128 + 1) + a_str_idx] == 3) {
          a_char = pad;
          b_char = SEQB[b_str_idx_p1 - 1];
        }
         else {
          if (ptr[b_str_idx * (128 + 1) + a_str_idx] == 1) {
            a_char = SEQA[a_str_idx_p1 - 1];
            b_char = pad;
          }
           else {
            a_char = SEQA[a_str_idx_p1 - 1];
            b_char = SEQB[b_str_idx_p1 - 1];
          }
        }
      }
      alignedA[a_str_idx] = a_char;
      alignedB[b_str_idx] = b_char;
      a_str_idx --;
      b_str_idx --;
    }
    a_str_idx = a_str_idx_p2 + 1;
    b_str_idx = b_str_idx_p2 + 1;
    b_idx --;
  }
  b_idx = 0 + 1;
  a_idx = 0 + 1;
  a_str_idx = ((b_idx - 1) * (a_idx - 1)) + (a_idx - 1);
  b_str_idx = ((b_idx - 1) * (a_idx - 1)) + (a_idx - 1);
/* Pad A */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_e_a