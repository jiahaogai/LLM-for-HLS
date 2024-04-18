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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    alignedB[b_idx] = '-';
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 5;
    alignedA[a_str_idx + 5] = '_';
    alignedA[a_str_idx + 4] = '_';
    alignedA[a_str_idx + 3] = '_';
    alignedA[a_str_idx + 2] = '_';
    alignedA[a_str_idx + 1] = '_';
    alignedA[a_str_idx] = SEQA[a_idx];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1LL : -1LL);
      row_up = a_idx * 5;
      up_left = M[row_up + b_idx];
      up = M[row_up + b_idx + 1];
      left = M[a_str_idx + b_idx + 1];
      max = (up_left + score);
      M[a_str_idx + b_idx] = left;
      if (left > up) {
        if (left > max) {
          M[a_str_idx + b_idx] = max;
          ptr[a_str_idx + b_idx] = row_up + b_idx;
        } else {
          ptr[a_str_idx + b_idx] = row_up + b_idx + 1;
        }
      } else {
        if (up > max) {
          M[a_str_idx + b_idx] = max;
          ptr[a_str_idx + b_idx] = row_up + b_idx + 1;
        } else {
          ptr[a_str_idx + b_idx] = row_up + b_idx;
        }
      }
    }
    row = a_str_idx + 4;
    b_idx = 4;
    r = 4;
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    traceback:
    while (row != 0) {
      b_str_idx = b_idx * 5;
      r = M[row + b_idx];
      if (r == left + score) {
        alignedB[b_str_idx] = SEQB[b_idx];
        row = ptr[row + b_idx];
        b_idx = b_str_idx;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      if (r == up + score) {
        alignedB[b_str_idx] = '-';
        row = ptr[row + b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      if (r == up_left + score) {
        alignedB[b_str_idx] = '-';
        alignedA[a_str_idx] = SEQA[a_idx];
        row = row_up;
        a_idx = a_str_idx;
        b_idx = b_str_idx;
      }
    }
  }
}