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
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication
// A is SEQA
// B is SEQB
//
// Score matrix is M
// ptr is ptr
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (b_idx = 1; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3_0}
    for (a_idx = 1; a_idx < 64; a_idx++) {
      score = (((int )SEQA[a_idx - 1]) == (((int )SEQB[b_idx - 1]))) ? 1 : (-1);
      row_up = (a_idx - 1) * 64;
      row = a_idx * 64;
      up_left = row_up + (b_idx - 1);
      up = row_up + b_idx;
      left = row + (b_idx - 1);
      max = M[up_left] + score;
      if (M[up] + (-1) > max) {
        max = M[up] + (-1);
        ptr[row + b_idx] = 2;
      }
      if (M[left] + score > max) {
        max = M[left] + score;
        ptr[row + b_idx] = 1;
      }
      M[row + b_idx] = max;
    }
  }
// Traceback
    a_idx = 63;
    b_idx = 63;
    a_str_idx = 0;
    b_str_idx = 0;
    r = M[a_idx * 64 + b_idx];
    while(1) {
      if (a_idx == 0 || b_idx == 0) {
        break;
      }
      if (ptr[a_idx * 64 + b_idx] == 0) {
        a_idx--;
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        r = M[a_idx * 64 + b_idx];
      }
      else if (ptr[a_idx * 64 + b_idx] == 1) {
        a_idx--;
        b_str_idx++;
        r = M[a_idx * 64 + b_idx] + (-1);
      }
      else {
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        r = M[a_idx * 64 + b_idx] + (-1);
      }
    }
    while(a_str_idx < 64) {
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedB[b_str_idx] = SEQA[a_idx];
      a_str_idx++;
      b_str_idx++;
      a_idx++;
    }
    alignedA[a_str_idx] = 0;
    alignedB[b_str_idx] = 0;
}