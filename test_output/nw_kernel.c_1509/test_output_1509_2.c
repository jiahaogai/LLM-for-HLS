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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_main:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_col_j:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[0] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      init_row_i:
      for (r = 1; r < 5; r++) {
        a_str_idx = r * 5;
        b_str_idx = b_idx * 5;
        up_left = M[(r - 1) * 5 + (a_idx - 1)];
        up = M[(r - 1) * 5 + a_idx];
        left = M[r * 5 + (a_idx - 1)];
        score = ((int )SEQA[a_str_idx + a_idx]) == ((int )SEQB[b_str_idx + b_idx]) ? (up_left + 1) : (up_left - 1);
        max = score > left ? (score > up ? score : up) : (left > up ? left : up);
        M[a_str_idx + b_idx] = max;
        row_up = a_str_idx + 5;
        if (max == left) {
          ptr[a_str_idx + b_idx] = ((char )60);
        }
        else {
          if (max == up) {
            ptr[a_str_idx + b_idx] = ((char )94);
          }
          else {
            ptr[a_str_idx + b_idx] = ((char )92);
          }
        }
      }
    }
  }
}