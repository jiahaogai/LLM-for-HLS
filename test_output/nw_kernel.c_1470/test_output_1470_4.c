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
  int idx_col;
  int idx_row;
  int idx_row_up;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = 0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_out_a:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = 5 * a_idx;
      b_str_idx = 5 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a_char = (((int )SEQA[a_str_idx])) - 0;
      b_char = (((int )SEQB[b_str_idx])) - 0;
      score = ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
      up_left = M[a_str_idx_p1 + b_str_idx_p1] + score;
      up = M[a_str_idx_p1 + b_str_idx] - 1;
      left = M[a_str_idx_p1 + b_str_idx_p1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx_p1 + a_str_idx_p1] = max;
      if (max == left) {
        ptr[b_str_idx_p1 + a_str_idx_p1] = 2;
      }
      
#pragma ACCEL PIVOT FACTOR=auto{__PIVOT__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_in:
      for (r = 0; r < 5; r++) {
        idx_row = r * 5;
        idx_row_up = (r + 1) * 5;
        idx_col = a_idx * 5;
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
        fill_in_a:
        for (rb = 0; rb < 5; rb++) {
          idx = idx_row + rb;
          idx_up = idx_row_up + rb;
          ptr[idx_up + idx_col] = (ptr[idx + idx_col] * 2 + ptr[idx_up + idx_col + 1]);
        }
      }
    }
  }
//#pragma endscop
}