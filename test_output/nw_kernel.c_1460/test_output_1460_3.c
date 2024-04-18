#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],int M[166],char ptr[166])
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
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (a_idx = 1; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_out_a_idx:
    for (b_idx = 1; b_idx < 5; b_idx++) {
      a_str_idx = ((5 * a_idx) - 1);
      b_str_idx = ((5 * b_idx) - 1);
      up_left = ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
      up = M[(b_str_idx - 1)] + ((int )SEQA[a_str_idx]) * - 1;
      left = M[a_str_idx + 1] + ((int )SEQB[b_str_idx]) * - 1;
      max = (up_left > (up > left?up : left))?up_left : (up > left?up : left);
      row_up = (b_str_idx - 1) * 5;
      M[b_str_idx + a_idx] = max;
      if (max == left) {
        ptr[b_str_idx + a_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == up) {
        ptr[b_str_idx + a_idx] = 1;
      }
    }
  }
// Traceback
  a_idx = 4;
  b_idx = 4;
  a_str_idx = ((5 * a_idx) - 1);
  b_str_idx = ((5 * b_idx) - 1);
  row = (a_idx + b_idx + 1);
// Pad A
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  pad_a:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
// Pad B
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  pad_b:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
// Fill out alignment score matrix
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  trace:
  while (1) {
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
    row = (a_idx + b_idx + 1);
    row_up = (b_idx - 1) * 5;
    if (ptr[row * 5 + a_idx] == 2) {
      alignedA[a_idx + b_idx] = SEQA[a_str_idx];
      alignedB[a_idx + b_idx] = SEQB[b_str_idx];
      a_str_idx--;
      b_str_idx--;
      a_idx++;
      b_idx++;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    if (ptr[row * 5 + a_idx] == 1) {
      alignedA[a_idx + b_idx] = SEQA[a_str_idx];
      alignedB[a_idx + b_idx] = '_';
      a_str_idx--;
      a_idx++;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    if (ptr[row * 5 + a_idx] == 0) {
      alignedA[a_idx + b_idx] = '_';
      alignedB[a_idx + b_idx] = SEQB[b_str_idx];
      b_str_idx--;
      b_idx++;
    }
  }
}