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
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx + 128] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx + 256] = '\0';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{128}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx + 128] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx + 256] = '\0';
  }
// Matrix initialization
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_M:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_B:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = SEQA[0] == SEQB[0] ? 1 : -1;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = -b_idx;
      }
      else if (b_idx == 0) {
        M[a_idx * 5] = -a_idx;
      }
      else {
        score = SEQA[a_idx] == SEQB[b_idx] ? 1 : -1;
        row_up = a_idx * 5;
        up_left = row_up + (b_idx - 1);
        up = row_up + b_idx;
        left = up_left;
        max = M[up_left] + score;
        if (M[up] + -a_idx > max) {
          max = M[up] + -a_idx;
          ptr[up] = left;
        }
        M[left] = max;
        if (M[up] + a_str_idx > max) {
          max = M[up] + a_str_idx;
          ptr[up] = up;
        }
        M[up] = max;
      }
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 5;
  b_str_idx = 5;
  r = M[b_idx * a_str_idx + a_idx];
align_E:
  while (a_idx || b_idx) {
//#A = strA[a_idx]
//#B = strB[b_idx]
    if (ptr[b_idx * a_str_idx + a_idx] == -b_idx) {
      b_idx = b_idx + 1;
    }
    else {
      if (ptr[b_idx * a_str_idx + a_idx] == -a_idx) {
        a_idx = a_idx + 1;
      }
      else {
        if (ptr[b_idx * a_str_idx + a_idx] == (b_idx + a_idx - 1) * -1) {
          a_idx = a_idx + 1;
          b_idx = b_idx + 1;
        }
        else {
          a_str_idx = b_idx;
          b_str_idx = a_idx;
        }
      }
    }
    if (a_idx < 5 || b_idx < 5) {
      r = M[b_idx * a_str_idx + a_idx];
    }
  }
}