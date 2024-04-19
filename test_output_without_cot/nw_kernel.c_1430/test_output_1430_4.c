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
    alignedA[a_idx] = '-';
  }
  init_row:
  for (a_idx = 64; a_idx < 78; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx - 64];
  }
  init_row:
  for (a_idx = 78; a_idx < 128 + 1; a_idx++) {
    alignedA[a_idx] = '-';
  }
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  init_col:
  for (b_idx = 64; b_idx < 78; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx - 64];
  }
  init_col:
  for (b_idx = 78; b_idx < 128 + 1; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_score:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_row:
    for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
      if (a_idx == 0) {
        if (b_idx == 0) {
          M[0] = 0;
          ptr[0] = 0;
        }
        else {
          M[b_idx] = M[b_idx * 64] + 1;
          ptr[b_idx] = 4;
        }
      }
      else if (b_idx == 0) {
        M[a_idx] = M[a_idx * 64] + 1;
        ptr[a_idx] = 2;
      }
      else {
        up_left = M[(a_idx - 1) * 64 + b_idx - 1] + ((SEQA[a_idx - 1] == SEQB[b_idx - 1]) ? 0 : 1);
        up = M[(a_idx - 1) * 64 + b_idx] + 1;
        left = M[a_idx * 64 + b_idx - 1] + 1;
        M[a_idx * 64 + b_idx] = (up_left < umax(up,left)) ? umax(up,left) : umax(up_left,0);
        if (M[a_idx * 64 + b_idx] == up_left) {
          if (a_idx > 1 && b_idx > 1 && SEQA[a_idx - 1] == SEQB[b_idx - 2] && SEQA[a_idx - 2] == SEQB[b_idx - 1]) {
            ptr[a_idx * 64 + b_idx] = 8;
          }
          else if (a_idx > 1 && b_idx > 1 && SEQA[a_idx - 1] == SEQB[b_idx - 1]) {
            ptr[a_idx * 64 + b_idx] = 6;
          }
          else {
            ptr[a_idx * 64 + b_idx] = 3;
          }
        }
        else {
          if (M[a_idx * 64 + b_idx] == up) {
            ptr[a_idx * 64 + b_idx] = 1;
          }
          else {
            ptr[a_idx * 64 + b_idx] = 2;
          }
        }
      }
    }
  }
  row = 128 + 1;
  b_idx = 128 + 1;
  a_str_idx = 128 + 1;
  b_str_idx = 128 + 1;
  score = M[row * 64 + b_idx];
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  traceback:
  while (a_idx != 0 || b_idx != 0) {
    if (ptr[row * 64 + b_idx] == 0) {
      a_idx--;
      b_idx--;
      a_str_idx--;
      b_str_idx--;
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedB[b_str_idx] = SEQB[b_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    else if (ptr[row * 64 + b_idx] == 1) {
      a_idx--;
      a_str_idx--;
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedB[b_str_idx] = '_';
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    else if (ptr[row * 64 + b_idx] == 2) {
      b_idx--;
      b_str_idx--;
      alignedA[a_str_idx] = '_';
      alignedB[b_str_idx] = SEQB[b_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    else if (ptr[row * 64 + b_idx] == 3) {
      a_idx--;
      b_idx--;
      a_str_idx--;
      b_str_idx--;
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedB[b_str_idx] = SEQB[b_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    else if (ptr[row * 64 + b_idx] == 4) {
      row_up = 64L * (