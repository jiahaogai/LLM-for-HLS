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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_mat:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    row = a_idx * 6;
    row_up = (a_idx - 1) * 6;
    a_str_idx = a_idx * 16;
    b_str_idx = a_idx * 4;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_mat:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[row] = ((int )SEQA[0]) * ((int )SEQB[0]) * score_match;
      }
      else if (a_idx == 0) {
        M[row] = ((int )SEQA[0]) * ((int )SEQB[b_idx]) * score_match + ((int )SEQA[0]) * score_gap + M[row + 6] * score_gap;
      }
      else if (b_idx == 0) {
        M[row] = ((int )SEQA[a_idx]) * ((int )SEQB[0]) * score_match + ((int )SEQB[0]) * score_gap + M[row_up] * score_gap;
      }
      else {
        up_left = M[row_up] + ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]);
        up = M[row + 6] + ((int )SEQA[a_idx]) * score_gap;
        left = M[row] + ((int )SEQB[b_idx]) * score_gap;
        M[row] = (up_left > left?up_left:left);
        M[row] = (M[row] > up?M[row]:up);
      }
      ptr[b_str_idx + b_idx] = -1;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      trace_mat:
      for (r = 0; r < 6; r++) {
        b_str_idx_tmp = b_str_idx + 2 * b_idx;
        if (((int )SEQA[r + a_idx]) == ((int )SEQB[b_idx])) {
          score = score_match;
        }
        else {
          score = score_mismatch;
        }
        max = M[row + r + 1] + score;
        up = M[row + r] + score_gap;
        left = M[row + r + 1] + score_gap;
        if (up_left > left) {
          up_left = up_left > up?up_left:up;
          ptr[b_str_idx_tmp] = 2;
        }
        else {
          if (up > left) {
            up = up > up_left?up:up_left;
            ptr[b_str_idx_tmp] = 1;
          }
          else {
            left = left > up?left:up;
            ptr[b_str_idx_tmp] = 0;
          }
        }
        M[row_a_idx] = left;
        row_a_idx = row_up;
        b_str_idx = b_str_idx_tmp;
      }
    }
  }
}