#pragma ACCEL PARALLEL FACTOR=auto{2}

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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    alignedB[b_idx] = '-';
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 5;
    alignedA[a_str_idx + 5] = '_';
    alignedA[a_str_idx + 4] = '_';
    alignedA[a_str_idx + 3] = '_';
    alignedA[a_str_idx + 2] = '_';
    alignedA[a_str_idx + 1] = '_';
    alignedA[a_str_idx + 0] = '_';
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      score = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]) * 1;
      row_up = a_idx * 5;
      up_left = M[row_up + b_idx];
      up = M[row_up + b_idx + 1];
      left = M[a_str_idx + b_idx + 1];
      max = (up_left + score > up ? up_left + score : up);
      max = (max > left ? max : left);
      M[a_str_idx + b_idx] = max;
      if (max == left) {
        ptr[a_str_idx + b_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_fma_reduce:
      for (r = 0; r < 4; r++) {
        score = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx + r + 1]) * 1;
        up = M[row_up + (b_idx + r + 1)];
        left = M[a_str_idx + (b_idx + r + 1)];
        max = (up_left + score > up ? up_left + score : up);
        max = (max > left ? max : left);
        M[a_str_idx + b_idx + r + 1] = max;
        if (max == left) {
          ptr[a_str_idx + b_idx + r + 1] = 2;
        }
      }
      alignedB[b_str_idx + 4] = '_';
      alignedB[b_str_idx + 3] = '_';
      alignedB[b_str_idx + 2] = '_';
      alignedB[b_str_idx + 1] = '_';
      alignedB[b_str_idx + 0] = '_';
      if (a_idx == 0 || b_idx == 0) {
        alignedA[a_str_idx + 4] = '-';
        alignedA[a_str_idx + 3] = '-';
        alignedA[a_str_idx + 2] = '-';
        alignedA[a_str_idx + 1] = '-';
        alignedA[a_str_idx + 0] = '*';
        alignedB[b_str_idx + 4] = '*';
        alignedB[b_str_idx + 3] = '-';
        alignedB[b_str_idx + 2] = '-';
        alignedB[b_str_idx + 1] = '-';
        alignedB[b_str_idx + 0] = '-';
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (a_idx == 0) {
        alignedA[a_str_idx + 4] = '*';
        alignedA[a_str_idx + 3] = '-';
        alignedA[a_str_idx + 2] = '-';
        alignedA[a_str_idx + 1] = '-';
        alignedA[a_str_idx + 0] = '-';
        alignedB[b_str_idx + 4] = '-';
        alignedB[b_str_idx + 3] = '*';
        alignedB[b_str_idx + 2] = '-';
        alignedB[b_str_idx + 1] = '-';
        alignedB[b_str_idx + 0] = '-';
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      if (b_idx == 0) {
        alignedA[a_str_idx + 4] = '-';
        alignedA[a_str_idx + 3] = '*';
        alignedA[a_str_idx + 2] = '-';
        alignedA[a_str_idx + 1] = '-';
        alignedA[a_str_idx + 0] = '-';
        alignedB[b_str_idx + 4] = '-';
        alignedB[b_str_idx + 3] = '-';
        alignedB[b_str_idx + 2] = '*';
        alignedB[b_str_idx + 1] = '-';
        alignedB[b_str_idx + 0] = '-';
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      if (a_idx == 0 && b_idx == 0) {
        alignedA[a_str_idx + 4] = '*';
        alignedA[a_str_idx + 3] = '-';
        alignedA[a_str_idx + 2] =