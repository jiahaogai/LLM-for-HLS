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
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_M:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    b_str_idx = (b_idx * 16) + 1;
    row = 0;
    row_up = 0 + b_idx;
    if (b_idx == 0) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      fill_M_row:
      for (a_idx = 0; a_idx < 5; a_idx++) {
        a_str_idx = (a_idx * 16) + 1;
        score = ((a_idx == 0) ? 0 : ((b_idx == 0) ? 0 : M[row_up * 16 + a_idx - 1]));
        M[row * 16 + a_idx] = score + ((SEQA[a_str_idx] == SEQB[b_str_idx]) ? 1 : (-1));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_M_row:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = (a_idx * 16) + 1;
      up_left = M[row_up * 16 + a_idx] + ((SEQA[a_str_idx] == SEQB[b_str_idx]) ? 1 : (-1));
      up = M[row_up * 16 + a_idx + 16] + (- 1);
      left = M[row * 16 + a_idx] + (- 1);
      max = (up_left > ((up > left) ? (up) : (left)));
      ptr[row * 16 + a_idx] = ((char )(a_str_idx - 1));
      row = a_idx + 1;
      row_up = a_idx + 1 + b_idx;
      M[row * 16 + a_idx] = max;
    }
  }
}