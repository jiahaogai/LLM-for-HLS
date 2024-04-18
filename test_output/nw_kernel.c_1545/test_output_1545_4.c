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
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    init_score_a:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 6] = ((int )'X') + ((int )'-') + 1 - ((int )SEQB[b_idx]);
      }
      else if (b_idx == 0) {
        M[a_idx * 6] = ((int )'X') + ((int )'-') + 1 - ((int )SEQA[a_idx]);
      }
      else {
        up_left = M[(a_idx - 1) * 6 + (b_idx - 1)];
        up = M[(a_idx - 1) * 6 + b_idx];
        left = M[a_idx * 6 + (b_idx - 1)];
        score = (((int )SEQA[a_idx]) == (((int )SEQB[b_idx]))) ? 1 : ((int )'X');
        max = (up_left > ((up > left)?up:left))?up_left:((up > left)?up:left);
        M[a_idx * 6 + b_idx] = score + max;
        if (max == left) {
          ptr[a_idx * 6 + b_idx] = 2;
        }
        else {
          if (max == up) {
            ptr[a_idx * 6 + b_idx] = 3;
          }
          else {
            ptr[a_idx * 6 + b_idx] = 1;
          }
        }
      }
    }
  }
  row_up = 5 * 6 - 1;
  row = 5 * 6 - 6;
  a_str_idx = 5;
  b_str_idx = 5;
/*
    #pragma ACCEL PIPELINE auto{__PIPE__L4}
    #pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    loop_row:
    for (a_idx = 5; a_idx >= 0; a_idx--) {
      b_idx = 0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      loop_col:
      for (; b_idx < 6; b_idx++) {
        score = M[a_idx * 6 + b_idx];
        if (b_idx == 5) {
          alignedB[a_idx + 1] = (char )'\0';
        }
        else {
          alignedB[a_idx + 1] = SEQB[b_idx];
        }
        if (a_idx == 5) {
          alignedA[b_idx + 1] = (char )'\0';
        }
        else {
          alignedA[b_idx + 1] = SEQA[a_idx];
        }
        if (b_idx == 0) {
          if (a_idx == 0) {
            ptr[a_idx * 6 + b_idx] = 0;
          }
          else {
            ptr[a_idx * 6 + b_idx] = 1 + 4 * row_up;
          }
        }
        else {
          if (a_idx == 0) {
            ptr[a_idx * 6 + b_idx] = 1 + 4 * row;
          }
          else {
            switch (ptr[a_idx * 6 + b_idx]) {
              case 1 + 4 * (row_up):
              case 2 + 4 * (row_up):
              case 3 + 4 * (row_up):
                ptr[a_idx * 6 + b_idx] = 1 + 4 * (row + row_up);
                break;
              case 1 + 4 * row:
                ptr[a_idx * 6 + b_idx] = 1 + 4 * row_up;
                break;
              case 2 + 4 * row:
                ptr[a_idx * 6 + b_idx] = 2 + 4 * row_up;
                break;
              case 3 + 4 * row:
                ptr[a_idx * 6 + b_idx] = 3 + 4 * row_up;
                break;
            }
          }
        }
        row_up = row;
        row = score;
      }
      a_str_idx -= 1;
      b_str_idx += 1;
    }
*/
}