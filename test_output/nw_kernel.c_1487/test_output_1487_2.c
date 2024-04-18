#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256])
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
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_col_j:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      alignedA[a_idx + 5] = ((int )SEQA[a_idx + b_idx]);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    fill_row:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      score = ((int )alignedA[a_idx]) * ((int )alignedB[b_idx]);
      up_left = M[a_str_idx + b_str_idx] + score;
      up = M[a_str_idx + b_str_idx + 5] + ((int )alignedA[a_idx]) * (-1);
      left = M[a_str_idx + b_str_idx + 1] + ((int )alignedB[b_idx]) * (-1);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_str_idx + b_str_idx] = max;
      ptr[a_str_idx + b_str_idx] = ((M[a_str_idx + b_str_idx] == up_left?2 : ((M[a_str_idx + b_str_idx] == up?1 : 0)));
      row_up = a_str_idx + 5;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      diag_j:
      for (r = 0; r < 5-1; r++) {
        row = row_up + 5;
        score = ((int )alignedA[r + 1 + a_idx]) * ((int )alignedB[b_idx + r + 1]);
        up = M[row] + score;
        left = M[row + 5] + ((int )alignedA[r + 1 + a_idx]) * (-1);
        max = (up > left?up : left);
        M[row] = max;
        ptr[row] = ((M[row] == up?1 : ((M[row] == left?2 : 0)));
      }
      row = row_up + 25;
      score = 0;
      up = M[row] + score;
      left = M[row + 5] + 0;
      max = (up > left?up : left);
      M[row] = max;
      ptr[row] = ((M[row] == up?1 : ((M[row] == left?2 : 0)));
    }
  }
}