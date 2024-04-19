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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    fill_in_a:
    for (a_idx = 0; a_idx < 64; a_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        score = 1;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      fill_in_b:
      for (b_str_idx = b_idx + 1; b_str_idx < 64; b_str_idx++) {
        up_left = M[((a_idx + 1) * 64) + (b_str_idx)];
        up = M[((a_idx + 1) * 64) + b_idx];
        left = M[(a_idx * 64) + (b_str_idx)];
        max = (up_left > ((up > left) ? (up) : (left)));
        row_up = (a_idx * 64);
        if (max == left) {
          M[row_up + b_str_idx] = left + (-1);
          ptr[row_up + b_str_idx] = 3;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L2}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
        if (max == up) {
          M[row_up + b_str_idx] = up + (-1);
          ptr[row_up + b_str_idx] = 2;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        if (max == up_left) {
          if (((int )SEQA[a_idx]) == ((int )SEQB[b_str_idx])) {
            score = 1;
          }
          if (((int )SEQA[a_idx]) != ((int )SEQB[b_str_idx])) {
            score = -1;
          }
          if (((int )SEQA[a_idx]) == ((int )SEQB[b_str_idx])) {
            a_str_idx = (a_idx + 1);
          }
          if (((int )SEQA[a_idx]) != ((int )SEQB[b_str_idx])) {
            a_str_idx = a_idx;
          }
          if (((int )SEQA[a_idx]) == ((int )SEQB[b_str_idx])) {
            b_str_idx = b_str_idx + 1;
          }
          if (((int )SEQA[a_idx]) != ((int )SEQB[b_str_idx])) {
            b_str_idx = b_idx;
          }
          M[row_up + b_str_idx] = (M[row_up + b_str_idx] + score);
          ptr[row_up + b_str_idx] = ((a_str_idx * 64) + b_str_idx);
        }
      }
    }
  }
  row = 63;
  b_idx = 63;
  a_idx = 62;
  r = 16640;
  while (a_idx > 0) {
    up_left = M[(a_idx * 64) + b_idx];
    up = M[(a_idx * 64) + (b_idx + 1)];
    left = M[(a_idx + 1) * 64 + b_idx];
    max = (up_left > ((up > left) ? (up) : (left)));
    if (max == left) {
      a_str_idx = (a_idx + 1);
      b_str_idx = b_idx;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    if (max == up) {
      a_str_idx = a_idx;
      b_str_idx = (b_idx + 1);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    if (max == up_left) {
      a_str_idx = ptr[r];
      b_str_idx = ptr[r + 1];
    }
    if (a_str_idx == b_idx) {
      alignedA[a_idx] = '-';
      alignedB[b_idx] = SEQB[b_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    if (a_str_idx == (b_idx + 1)) {
      alignedA[a_idx] = SEQA[a_idx];
      alignedB[b_idx] = '-';
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    if (((int )alignedA[a_idx]) == ((int )alignedB[b_idx])) {
      score = 1;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    if (((int )alignedA[a_idx]) != ((int )alignedB[b_idx])) {
      score = -1;
    }
    M[r] = ((short )((int )alignedA[a_idx] == (int )alignedB[b_idx]));
    r--;
    a_idx = a_str_idx;
    b_idx = b_str_idx;
  }
  alignedA[0] = '-';
  alignedB[0] = '-';
}