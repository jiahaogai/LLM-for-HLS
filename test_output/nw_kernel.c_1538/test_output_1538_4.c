#pragma ACCEL kernel

void needwun(char seq1[128],char seq2[128],char aligned_seq1[128],char aligned_seq2[128],int score_matrix[256][256],int8_t ptr_matrix[128][128])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int c;
  int _in_row;
  int _in_col;
  int _in_row_up;
  int _in_col_up;
  char _in_val_up;
  char _in_val;
  char _in_val_left;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (r = 0; r < 128 + 1; r++) {
    aligned_seq1[r] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (r = 0; r < 128 + 1; r++) {
    aligned_seq2[r] = ((char )0);
  }
/* Row Initialization */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_row_up:
  for (r = 0; r < 128; r++) {
    aligned_seq1[r] = seq1[r];
  }
/* Column Initialization */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col_up:
  for (r = 0; r < 128; r++) {
    aligned_seq2[r] = seq2[r];
  }
/* Matrix Initialization */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (r = 1; r < 128 + 1; r++) {
    	#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_out_up:
    for (c = 1; c < 128 + 1; c++) {
      if (r <= 128 - 1 && c <= 128 - 1) {
        up_left = ((int )aligned_seq1[r - 1]) * ((int )aligned_seq2[c - 1]) + score_matrix[((int )aligned_seq1[r])][((int )aligned_seq2[c])];
        up = ((int )aligned_seq1[r - 1]) * score_matrix[((int )aligned_seq2[c])][((int )aligned_seq1[r])] + score_matrix[((int )aligned_seq1[r])][((int )aligned_seq2[c])];
        left = ((int )aligned_seq2[c - 1]) * score_matrix[((int )aligned_seq1[r])][((int )aligned_seq2[c])] + score_matrix[((int )aligned_seq1[r])][((int )aligned_seq2[c])];
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        row_up = r - 1;
        _in_row = r;
        _in_col = c - 1;
        _in_row_up = r - 1;
        _in_col_up = c;
        _in_val_up = aligned_seq1[row_up];
        _in_val = aligned_seq1[_in_row];
        _in_val_left = aligned_seq2[_in_col];
        if (max == left) {
          aligned_seq1[_in_row] = _in_val_left;
          aligned_seq2[_in_col] = _in_val;
          ptr_matrix[(_in_row * 128) + _in_col] = 2;
        }
         else {
          if (max == up) {
            aligned_seq1[_in_row] = _in_val_up;
            aligned_seq2[_in_col] = _in_val;
            ptr_matrix[(_in_row * 128) + _in_col] = 1;
          }
           else {
            aligned_seq1[_in_row] = _in_val_left;
            aligned_seq2[_in_col] = _in_val_up;
            ptr_matrix[(_in_row * 128) + _in_col] = 3;
          }
        }
        score = max;
      }
    }
  }
}