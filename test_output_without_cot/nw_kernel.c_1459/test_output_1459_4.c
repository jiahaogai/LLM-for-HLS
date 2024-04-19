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
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  init_score:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx + 64] = SEQA[a_idx];
    a_str_idx = a_idx << 6;
    b_str_idx = 0;
    score = a_str_idx;
    ptr[score] = -1;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_row:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      alignedB[b_idx + 64] = SEQB[b_idx];
      b_str_idx += 16;
      score = b_str_idx;
      if (a_idx == 0) {
        M[score] = ((int )SEQB[b_idx]) << 1;
      }
      
      else {
        M[score] = ((int )alignedA[a_idx + 0]) * ((int )alignedB[b_idx + 64]) + ((int )alignedA[a_idx + 64]) * ((int )alignedB[b_idx + 0]) - ((int )alignedA[a_idx + 64]) * ((int )alignedB[b_idx + 64]);
      }
      ptr[score] = a_idx + 64;
    }
  }
  row = 64;
  row_up = 128;
  a_str_idx = 64 << 6;
  b_str_idx = 64;
  score = a_str_idx + b_str_idx;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  loop_row:
  for (r = 1; r < 64; r++) {
    a_idx = r + 64;
    a_str_idx = a_idx << 6;
    up_left = ((int )alignedA[a_idx - 1]) * ((int )alignedB[b_idx - 1]) - ((int )alignedA[a_idx - 1]) * ((int )alignedB[b_idx + 64]) - ((int )alignedA[a_idx + 64]) * ((int )alignedB[b_idx - 1]) + ((int )alignedA[a_idx + 64]) * ((int )alignedB[b_idx + 64]);
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loop_col:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      b_str_idx += 16;
      score = b_str_idx;
      up = M[score + up_str_idx] + ((int )alignedA[a_idx - 1]) * ((int )alignedB[b_idx + 64]) - ((int )alignedA[a_idx + 64]) * ((int )alignedB[b_idx - 1]);
      left = M[score] + ((int )alignedB[b_idx - 1]) * ((int )alignedA[a_idx + 64]) - ((int )alignedB[b_idx + 64]) * ((int )alignedA[a_idx - 1]);
      max = (up > left?up : left);
      M[score] = max + ((int )alignedA[a_idx]) * ((int )alignedB[b_idx]);
      if (max == left) {
        ptr[score] = a_idx - 1;
      }
      
      else if (max == up) {
        ptr[score] = a_idx - 1 + 64;
      }
      
      else {
        ptr[score] = a_idx - 1 + up_str_idx;
      }
    }
    up_str_idx = a_str_idx;
  }
  b_idx = 64;
  score = a_str_idx + b_idx;
  max = M[score];
  a_idx = 0;
  b_idx = 0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  trace_back:
  while (a_idx < 64 && b_idx < 64) {
    score = a_idx << 6 | b_idx << 6;
    if (ptr[score] == -1) {
      a_idx = a_idx + 1;
      b_idx = b_idx + 1;
    }
    
    else if (ptr[score] < a_idx) {
      b_idx = b_idx + 1;
    }
    
    else if (ptr[score] > a_idx) {
      a_idx = a_idx + 1;
    }
    
    else {
      a_idx = a_idx + 1;
      b_idx = b_idx + 1;
    }
    if (M[a_idx << 6 | b_idx << 6] > max) {
      max = M[a_idx << 6 | b_idx << 6];
    }
  }
}