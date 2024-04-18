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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_row:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[a_idx * 5 + b_idx] = a_idx * 5 + b_idx;
        ptr[a_idx * 5 + b_idx] = 0;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      score_row:
      for (b_str_idx = 0; b_str_idx < b_idx; b_str_idx++) {
        up_left = M[a_idx * 5 + b_str_idx] + ((int )SEQA[a_idx] != (int )SEQB[b_idx]);
        up = M[(a_idx - 1) * 5 + b_idx + 1] + ((int )SEQA[a_idx - 1] != (int )SEQB[b_idx]);
        left = M[a_idx * 5 + b_str_idx + 1] + ((int )SEQA[a_idx] != (int )SEQB[b_idx - 1]);
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[a_idx * 5 + b_idx] = max;
        if (max == left) {
          ptr[a_idx * 5 + b_idx] = 2;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
        if (max == up) {
          ptr[a_idx * 5 + b_idx] = 1;
        }
      }
    }
  }
  row = 4;
  b_idx = 4;
  a_idx = 4;
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx * 5;
  score = M[a_str_idx + b_str_idx];
  r = a_str_idx;
/*
    traceback:
      row = 4
      b_idx = 4
      a_idx = 4
      a_str_idx = a_idx * 5
      b_str_idx = b_idx * 5
      score = M[a_str_idx + b_str_idx]
      r = a_str_idx
      while (a_idx > 0 || b_idx > 0) {
        if (b_idx == 0) {
          a_idx--;
          a_str_idx = a_idx * 5;
          b_str_idx = b_idx * 5;
          score = M[a_str_idx + b_str_idx];
        }
        else if (a_idx == 0) {
          b_idx--;
          a_str_idx = a_idx * 5;
          b_str_idx = b_idx * 5;
          score = M[a_str_idx + b_str_idx];
        }
        else {
          row_up = a_str_idx;
          row = b_str_idx;
          up_left = M[a_str_idx + b_str_idx] + ((int )SEQA[a_idx] != (int )SEQB[b_idx]);
          up = M[row_up + b_str_idx + 1] + ((int )SEQA[a_idx - 1] != (int )SEQB[b_idx]);
          left = M[a_str_idx + row + 1] + ((int )SEQA[a_idx] != (int )SEQB[b_idx - 1]);
          max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
          if (max == left) {
            b_idx--;
            b_str_idx = b_idx * 5;
            score = left;
          }
          else {
            if (max == up) {
              a_idx--;
              a_str_idx = a_idx * 5;
              score = up;
            }
            else {
              a_idx--;
              b_idx--;
              a_str_idx = a_idx * 5;
              b_str_idx = b_idx * 5;
              score = up_left;
            }
          }
        }
        if (ptr[a_str_idx + b_str_idx] == 0) {
          alignedA[r] = '-';
          alignedB[r] = SEQB[b_idx];
          r++;
        }
        else {
          if (ptr[a_str_idx + b_str_idx] == 1) {
            alignedA[r] = SEQA[a_idx];
            alignedB[r] = '-';
            r++;
          }
          else {
            alignedA[r] = SEQA[a_idx];
            alignedB[r] = SEQB[b_idx];
            r++;
          }
        }
      }
      alignedA[r] = 0;
      alignedB[r] = 0;
*/
}