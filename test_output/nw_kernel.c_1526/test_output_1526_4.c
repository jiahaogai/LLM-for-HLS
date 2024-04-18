#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
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
  int flatten_idx;
  
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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = ((int )SEQA[0]) * ((int )SEQB[0]) - 1;
      }
      else if (a_idx == 0) {
        M[b_idx * 5] = ((int )SEQA[0]) * ((int )SEQB[b_idx]) - 1;
      }
      else if (b_idx == 0) {
        M[a_idx * 5] = ((int )SEQA[a_idx]) * ((int )SEQB[0]) - 1;
      }
      else {
        a_str_idx = 5 * a_idx;
        b_str_idx = 5 * b_idx;
        a_str_idx_p1 = a_str_idx + 1;
        b_str_idx_p1 = b_str_idx + 1;
        up_left = M[b_str_idx_p1 + a_str_idx] + ((int )SEQA[a_str_idx_p1]) * ((int )SEQB[b_str_idx_p1]) - 1;
        up = M[b_str_idx_p1 + a_str_idx_p1] - 1;
        left = M[b_str_idx + a_str_idx_p1] + ((int )SEQA[a_str_idx_p1]) * ((int )SEQB[b_str_idx]) - 1;
        max = (up_left > ((int )0 ? up_left : -up_left)) ? up_left : ((int )0 ? up : -up);
        max = (left > max ? left : max);
        M[b_str_idx_p1 + a_str_idx_p1] = ((int )SEQA[a_str_idx_p1]) * ((int )SEQB[b_str_idx_p1]) + max;
//flatten
        flatten_idx = 0;
        if (a_idx > 0) {
          flatten_idx += 5;
        }
        if (b_idx > 0) {
          flatten_idx += 40;
        }
        idx_row = b_idx;
        idx_col = a_idx;
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
        score_row:
        for (r = 0; r < 4; r++) {
          row = 5 * idx_row;
          row_up = 5 * (idx_row + 1);
          b_char = SEQB[row_up + idx_col + 1];
          u = M[row_up + idx_col] - 1;
          l = M[row + idx_col + 1] - 1;
          if (b_char == SEQA[row_up + idx_col + 1]) {
            score = u;
          }
          else {
            score = l;
          }
          if (score == ((int )0 ? up : -up)) {
            ptr[flatten_idx + r] = 2;
            idx = row_up + idx_col + 1;
          }
          else {
            if (score == ((int )0 ? left : -left)) {
              ptr[flatten_idx + r] = 1;
              idx = row + idx_col + 1;
            }
            else {
              ptr[flatten_idx + r] = 0;
              idx = up_left < ((int )0 ? left : -left) ? up_left < ((int )0 ? u : -u) ? up_left : ((int )0 ? u : -u) : left < ((int )0 ? u : -u) ? left : ((int )0 ? u : -u);
              if (up_left < ((int )0 ? left : -left)) {
                ptr[flatten_idx + r] = 3;
              }
            }
          }
        }
      }
    }
  }
}