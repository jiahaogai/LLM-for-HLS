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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  char a;
  char b;
  char state;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  loop_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_col:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      a_idx_up = (a_idx + 1) * 64;
      b_idx_up = (b_idx + 1);
      a_idx_left = a_idx * 64;
      b_idx_left = b_idx * 64;
      up_left = M[a_idx_left + b_idx] + SEQA[a_idx] * SEQB[b_idx];
      up = M[a_idx_up + b_idx] + SEQA[a_idx] * SEQB[b_idx_left];
      left = M[a_idx_left + b_idx_up] + SEQA[a_idx_up] * SEQB[b_idx];
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      state = (up_left > ((up > left) ? up : left)) ? 4 : ((up > left) ? 3 : 2);
/* Update the score matrix. */
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      loop_state:
      for (r = 0; r < 32; r++) {
        if (state == 4) {
          row = a_idx_up + b_idx_up;
        }
        else {
          if (state == 3) {
            row = a_idx_up + b_idx;
          }
          else {
            row = a_idx_left + b_idx_up;
          }
        }
        row_up = row + 64;
        score = M[row] + (((int )SEQA[r]) * ((int )SEQB[b_idx]) * - 1);
        up = M[row_up] + (((int )SEQA[r]) * ((int )SEQB[b_idx_left]) * - 1);
        left = M[row + 1] + (((int )SEQA[r]) * ((int )SEQB[b_idx_up]) * - 1);
        max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
        state = (up_left > ((up > left) ? up : left)) ? 4 : ((up > left) ? 3 : 2);
        M[row] = max;
        ptr[row] = state;
      }
    }
  }
// TraceBack
  a_idx = 63;
  b_idx = 63;
  score = M[a_idx * 64 + b_idx];
/* TraceBack */
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    row = a_idx * 64 + b_idx;
    state = ptr[row];
    if (state == 4) {
      a = SEQA[a_idx];
      b = SEQB[b_idx];
      alignedA[a_idx + - 1] = a;
      alignedB[b_idx + - 1] = b;
      a_idx = a_idx + 1;
      b_idx = b_idx + 1;
    }
    else {
      if (state == 3) {
        a = SEQA[a_idx];
        b = SEQB[b_idx_left];
        alignedA[a_idx + - 1] = a;
        alignedB[b_idx + - 1] = b;
        a_idx = a_idx + 1;
      }
      else {
        if (state == 2) {
          a = SEQA[a_idx_up];
          b = SEQB[b_idx];
          alignedA[a_idx + - 1] = a;
          alignedB[b_idx + - 1] = b;
          b_idx = b_idx + 1;
        }
      }
    }
  }
}