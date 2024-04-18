c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = -1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{128}
  fill_out:
  for (a_idx = 1; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    fill_in:
    for (b_idx = 1; b_idx < 5; b_idx++) {
      a_str_idx = 5 * a_idx;
      b_str_idx = 5 * b_idx;
      up_left = M[a_str_idx + b_idx - 1] + ((int )SEQA[a_idx - 1] != (int )SEQB[b_idx - 1]);
      up = M[a_str_idx + b_idx] + ((int )SEQA[a_idx - 1] == (int )45);
      left = M[b_str_idx + a_idx] + ((int )SEQB[b_idx - 1] == (int )45);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx + a_idx] = max;
      row_up = b_str_idx + a_idx - 1;
      if (max == left) {
        ptr[b_str_idx + a_idx] = row_up;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      trace:
      for (r = 1; r < a_idx; r++) {
        row = r * 5;
        row_up = (r - 1) * 5;
        up = M[row + b_idx] + ((int )SEQA[r] == (int )45);
        left = M[row_up + a_idx] + ((int )SEQB[a_idx - 1] == (int )45);
        up_left = M[row_up + b_idx] + ((int )SEQA[r] != (int )SEQB[a_idx - 1]);
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[row + a_idx] = max;
        if (max == left) {
          ptr[row + a_idx] = row_up;
        }
      }
    }
  }
// Traceback
  a_idx = 4;
  b_idx = 4;
  score = M[a_idx * 5 + b_idx];
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx;
  alignedA[0] = (char )'\0';
  alignedB[0] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  traceback:
  while (1) {
    if (b_idx == 0) {
      break;
    }
    if (a_idx == 0) {
      b_idx--;
      alignedA[strlen(alignedA)] = '_';
      alignedB[strlen(alignedB)] = SEQB[b_idx];
    }
    else if (b_idx == 0) {
      a_idx--;
      alignedA[strlen(alignedA)] = SEQA[a_idx];
      alignedB[strlen(alignedB)] = '_';
    }
    else if (M[a_str_idx + b_idx] == (M[a_str_idx + b_idx - 1] + (int )SEQA[a_idx - 1] != (int )SEQB[b_idx - 1])) {
      a_idx--;
      b_idx--;
      alignedA[strlen(alignedA)] = SEQA[a_idx];
      alignedB[strlen(alignedB)] = SEQB[b_idx];
    }
    else if (M[a_str_idx + b_idx] == (M[a_str_idx + b_idx - 1] + (int )SEQA[a_idx - 1] == (int )45)) {
      a_idx--;
      alignedA[strlen(alignedA)] = SEQA[a_idx];
      alignedB[strlen(alignedB)] = '_';
    }
    else if (M[a_str_idx + b_idx] == (M[b_str_idx + a_idx - 1] + (int )SEQB[b_idx - 1] != (int )45)) {
      b_idx--;
      alignedA[strlen(alignedA)] = '_';
      alignedB[strlen(alignedB)] = SEQB[b_idx];
    }
    else if (M[a_str_idx + b_idx] == (M[b_str_idx + a_idx - 1] + (int )SEQB[b_idx - 1] == (int )45)) {
      b_idx--;
      alignedA[strlen(alignedA)] = '_';
      alignedB[strlen(alignedB)] = SEQB[b_idx];
    }
  }
}