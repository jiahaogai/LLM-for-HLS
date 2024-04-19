#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char ptr[128],int M[166416])
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
  for (a_idx = 0; a_idx < 128; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    M[b_idx] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 128; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (a_idx - 1) * 128;
      row = a_idx * 128;
      up_left = M[row_up + (b_idx - 1)] + score;
      up = M[row_up + b_idx] - 1;
      left = M[row + (b_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + b_idx] = max;
      a_str_idx = a_idx * 4;
      b_str_idx = b_idx * 4;
      if (max == left) {
        ptr[b_str_idx] = ((char )60);
        ptr[b_str_idx + 1] = ((char )62);
        ptr[b_str_idx + 2] = ((char )45);
        ptr[b_str_idx + 3] = ((char )0);
      }
       else {
        if (max == up) {
          ptr[b_str_idx] = ((char )62);
          ptr[b_str_idx + 1] = ((char )62);
          ptr[b_str_idx + 2] = ((char )45);
          ptr[b_str_idx + 3] = ((char )0);
        }
         else {
          ptr[b_str_idx] = ((char )62);
          ptr[b_str_idx + 1] = ((char )60);
          ptr[b_str_idx + 2] = ((char )45);
          ptr[b_str_idx + 3] = ((char )0);
        }
      }
    }
  }
// Traceback
  a_idx = 127;
  b_idx = 127;
  a_str_idx = (a_idx * 4);
  b_str_idx = (b_idx * 4);
  alignedA[a_idx] = ((char )'\0');
  alignedB[b_idx] = ((char )'\0');
// Backtracking
  r = 0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace:
  while (1) {
    if (((int )ptr[b_str_idx]) == 62) {
      alignedA[a_idx] = SEQA[a_idx - 1];
      alignedB[b_idx] = SEQB[b_idx - 1];
      a_idx = a_idx - 1;
      b_idx = b_idx - 1;
      a_str_idx = (a_idx * 4);
      b_str_idx = (b_idx * 4);
    }
     else {
      if (((int )ptr[b_str_idx]) == 60) {
        alignedA[a_idx] = SEQA[a_idx - 1];
        alignedB[b_idx] = '-';
        a_idx = a_idx - 1;
        b_str_idx = (b_idx * 4);
      }
       else {
        if (((int )ptr[b_str_idx]) == 45) {
          alignedA[a_idx] = '-';
          alignedB[b_idx] = SEQB[b_idx - 1];
          b_idx = b_idx - 1;
          a_str_idx = (a_idx * 4);
          b_str_idx = (b_idx * 4);
        }
      }
    }
    if (a_idx == 0) {
      if (b_idx == 0) {
        break;
      }
      else {
        b_idx = 0;
        a_str_idx = 0;
        b_str_idx = 0;
      }
    }
  }
}