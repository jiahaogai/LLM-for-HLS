#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641])
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
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    b_str_idx = (b_idx * 1) + 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    fill_row:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      a_str_idx = (a_idx * 1) + 1;
      up_left = M[(0 + (0 * 64))];
      up = M[((b_idx - 1) + (a_idx * 64))];
      left = M[((a_idx - 1) + (b_idx * 64))];
      if (((int )SEQA[a_str_idx - 1]) == ((int )SEQB[b_str_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      max = (up_left + score);
      row_up = (b_idx - 1);
      if (up > max) {
        max = up;
        row = row_up;
      }
      row_left = a_idx - 1;
      if (left > max) {
        max = left;
        row = row_left;
      }
      M[(a_idx + (b_idx * 64))] = max;
      if (max == ((int )0)) {
        alignedA[a_idx] = ((char )'\000');
        alignedB[b_idx] = ((char )'\000');
      }
       else {
        if (row == row_up) {
          alignedA[a_idx] = alignedA[a_idx - 1];
          alignedB[b_idx] = ((char )SEQB[b_str_idx - 1]);
        }
         else {
          if (row == row_left) {
            alignedA[a_idx] = ((char )SEQA[a_str_idx - 1]);
            alignedB[b_idx] = alignedB[b_idx - 1];
          }
           else {
            r = a_idx - 1;
            r = b_idx - 1;
            alignedA[a_idx] = ((char )SEQA[a_str_idx - 1]);
            alignedB[b_idx] = ((char )SEQB[b_str_idx - 1]);
          }
        }
      }
    }
  }
}