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
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * (-1);
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * (-1);
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (a_idx = 1; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in_a:
    for (b_idx = 1; b_idx < 5; b_idx++) {
      score = ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) * 1;
      row_up = (a_idx - 1) * 5;
      row = a_idx * 5;
      up_left = row_up + (b_idx - 1);
      up = row_up + b_idx;
      left = row + (b_idx - 1);
      max = M[up_left] + score;
      if (M[up] + (-1) > max) {
        max = M[up] + (-1);
        ptr[left] = 2;
      }
      if (M[left] + (-1) > max) {
        max = M[left] + (-1);
        ptr[left] = 1;
      }
      M[row + b_idx] = max;
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row_up = (a_idx - 1) * 5;
    row = a_idx * 5;
    up_left = row_up + (b_idx - 1);
    up = row_up + b_idx;
    left = row + (b_idx - 1);
    max = M[up_left] + S[a_idx - 1] * S[b_idx - 1];
    if (M[up] + (- 1) > max) {
      max = M[up] + (- 1);
      ptr[left] = 2;
    }
    if (M[left] + (- 1) > max) {
      max = M[left] + (- 1);
      ptr[left] = 1;
    }
*/
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (1) {
    if (ptr[b_idx * 5 + a_idx] == 0) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
      a_idx--;
      b_idx--;
    }
    else if (ptr[b_idx * 5 + a_idx] == 1) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = '-';
      a_idx--;
    }
    else if (ptr[b_idx * 5 + a_idx] == 2) {
      alignedA[a_str_idx++] = '-';
      alignedB[b_str_idx++] = SEQB[b_idx];
      b_idx--;
    }
    if (a_idx == 0) {
      break;
    }
  }
}