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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      up_left = M[(b_idx - 1) * 64 + (a_idx - 1)];
      up = M[b_idx * 64 + (a_idx - 1)];
      left = M[(b_idx - 1) * 64 + a_idx];
      score = SEQA[a_idx] == SEQB[b_idx] ? 1 : -1;
      max = (up_left + score) > (up + score) ? (up_left + score) : (up + score);
      max = left > max ? left : max;
      M[b_idx * 64 + a_idx] = max;
      row_up = b_idx * 64 + (a_idx - 1);
      if (max == left) {
        ptr[b_idx * 64 + a_idx] = row_up;
      }
      else {
        if (max == up) {
          ptr[b_idx * 64 + a_idx] = row_up + 64;
        }
        else {
          ptr[b_idx * 64 + a_idx] = row_up + 65;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    trace_str: for (r = 0; r < 64; r++) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
      if (ptr[b_idx * 64 + a_idx] == ((b_idx + 1) * 64) + (a_idx + 1)) {
        a_idx--;
        b_idx--;
      }
      else {
        if (ptr[b_idx * 64 + a_idx] == ((b_idx + 1) * 64) + a_idx) {
          b_idx--;
        }
        else {
          a_idx--;
        }
      }
    }
    trace_str: for (r = 0; r < 64 + 1; r++) {
      alignedA[a_str_idx++] = '-';
    }
    trace_str: for (r = 0; r < 64 + 1; r++) {
      alignedB[b_str_idx++] = '-';
    }
*/
}