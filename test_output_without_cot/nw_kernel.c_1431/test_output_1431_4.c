#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],int ptr[16641])
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
  for (a_idx = 0; a_idx < 65; a_idx++) {
    M[a_idx] = a_idx * (-1);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 65; b_idx++) {
    M[b_idx * 64] = b_idx * (-1);
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  fill_out:
  for (b_idx = 1; b_idx < 65; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 65; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = (b_idx - 1) * 64;
      row = b_idx * 64;
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] - 1;
      left = M[row + (a_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = ((b_idx - 1) * 64) + (a_idx - 1);
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = ((b_idx - 1) * 64) + a_idx;
        }
         else {
          ptr[row + a_idx] = ((b_idx - 1) * 64) + a_idx;
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
    trace_out:
    while (a_idx > 0 || b_idx > 0) {
      r = b_idx * 64 + a_idx;
      if (M[r] >= 0) {
        a_str_idx++;
        b_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        a_idx = ptr[r];
        b_idx = ptr[r + 1];
      }
       else {
        if (a_idx == 0 && b_idx == 0) {
          break;
        }
         else {
          if (a_idx == 0) {
            a_str_idx++;
            alignedA[a_str_idx] = '-';
            b_str_idx++;
            alignedB[b_str_idx] = SEQB[b_idx];
            b_idx = ptr[r + 1];
          }
           else {
            if (b_idx == 0) {
              a_str_idx++;
              alignedA[a_str_idx] = SEQA[a_idx];
              b_str_idx++;
              alignedB[b_str_idx] = '-';
              a_idx = ptr[r];
            }
          }
        }
      }
    }
  */
}