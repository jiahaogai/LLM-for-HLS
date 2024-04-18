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
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a_char;
  char b_char;
  int idx;
  int next_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 16;
    a_str_idx_p1 = (a_idx + 1) * 16;
    row_up = ((5 + 1) * 16) + a_idx;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    diag:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 16;
      b_str_idx_p1 = (b_idx + 1) * 16;
      score = ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
      up_left = M[row_up + b_idx] + score;
      up = M[a_str_idx_p1 + b_idx] - ((int )'A') * ((int )'A');
      left = M[row_up + b_str_idx_p1] - ((int )'A') * ((int )'A');
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_str_idx_p1 + b_str_idx_p1] = max;
      if (max == left) {
        ptr[a_str_idx_p1 + b_str_idx_p1] = ((char )60);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      col:
      for (r = 1; r < 16; r++) {
        idx = a_str_idx + r;
        next_idx = a_str_idx_p1 + b_str_idx;
        score = ((int )SEQA[idx]) * ((int )SEQB[b_str_idx_p1]);
        up = M[next_idx] - ((int )'A') * ((int )'A');
        left = M[idx + b_str_idx_p1] - ((int )'A') * ((int )'A');
        max = (up + score > left?up + score : left);
        M[next_idx + b_str_idx_p1] = max;
        if (max == left) {
          ptr[next_idx + b_str_idx_p1] = ((char )94);
        }
      }
    }
  }
  a_idx = 5;
  b_idx = 5;
  a_str_idx = 56;
  b_str_idx = 56;
}