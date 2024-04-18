#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[1026],char alignedB[1026],char score_matrix[128][128],char ptr_matrix[128][128],char ptr_row[128],char ptr_col[128])
{
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
  int row;
  int row_up;
  int col;
  int col_up;
  int index;
  int row_end;
  int col_end;
  int row_step;
  int col_step;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (row = 0; row < 128 + 1; row++) {
    ptr_row[row] = row;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (row = 0; row < 128 + 1; row++) {
    ptr_col[row] = row;
  }
// Matrix initialization
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  fill_out:
  for (row = 1; row < 128 + 1; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    fill_in:
    for (col = 1; col < 128 + 1; col++) {
      if (((int )SEQA[row - 1]) == ((int )SEQB[col - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      if (row == 1) {
        index = 0;
      }
       else {
        index = ptr_col[row - 1] * 64;
      }
      if (col == 1) {
        index_row_up = 0;
      }
       else {
        index_row_up = ptr_col[col - 1] * 64;
      }
      if (row == 1) {
        index_col_up = 0;
      }
       else {
        index_col_up = ptr_row[row - 1] * 64;
      }
      up_left = score_matrix[index + index_row_up + index_col_up] + ((int )ptr_matrix[index + index_row_up + index_col_up]);
      up = score_matrix[index + index_row_up + 64] + ((int )ptr_matrix[index + index_row_up + 64]);
      left = score_matrix[index + 64 + index_col_up] + ((int )ptr_matrix[index + 64 + index_col_up]);
      score_matrix[index + 64] = ((up_left > ((up + left) > 0?((up + left)) : 0))?up_left : ((up + left) > 0?((up + left)) : 0));
      ptr_matrix[index + 64] = ((up_left == score_matrix[index + 64])?ptr_matrix[index + index_row_up + index_col_up] : ((up + left) == score_matrix[index + 64]?ptr_matrix[index + index_row_up + 64] : ptr_matrix[index + 64 + index_col_up]));
    }
  }
// TraceBack
  row_end = 128 + 1;
  col_end = 128 + 1;
  row_step = 1;
  col_step = 1;
  row = row_end - 1;
  col = col_end - 1;
  alignedA[col_step * (128) - 1] = '\0';
  alignedB[row_step * (128) - 1] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace_out:
  while (1) {
//#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    trace_in:
    while (1) {
      if (row > 0 && col > 0) {
        index = col * 64;
        index_row_up = (col - 1) * 64;
        index_col_up = row * 64;
        up_left = score_matrix[index + index_row_up + index_col_up];
        up = score_matrix[index + index_row_up + 64];
        left = score_matrix[index + 64 + index_col_up];
        u = up_left + ((int )ptr_matrix[index + index_row_up + index_col_up]);
        l = left + ((int )ptr_matrix[index + 64 + index_col_up]);
        if (u < l) {
          if (u < 0) {
            u = 0;
          }
          alignedA[col_step * (row) - 1] = ((char )SEQA[row - 1]);
          alignedB[col_step * (col) - 1] = ((char )SEQB[col - 1]);
          row = row - 1;
          col = ptr_row[col];
        }
         else {
          if (l < 0) {
            l = 0;
          }
          alignedA[col_step * (row) - 1] = ((char )SEQA[row - 1]);
          alignedB[col_step * (col) - 1] = ((char )SEQB[col - 1]);
          col = col - 1;
          row = ptr_col[row];
        }
      }
       else {
        break;
      }
    }
    if (row == 0 || col == 0) {
      break;
    }
  }
}