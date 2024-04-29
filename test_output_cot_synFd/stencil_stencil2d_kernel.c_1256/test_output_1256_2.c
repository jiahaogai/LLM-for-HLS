#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_row_up:
/* Standardize from: for(row_up = -1; row_up <= 1; row_up++) {...} */
  for (row_up = -1; row_up <= 1; row_up++) {
    int _in_row_up = 0 + row_up;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_col_up:
/* Standardize from: for(col_up = -1; col_up <= 1; col_up++) {...} */
    for (col_up = -1; col_up <= 1; col_up++) {
      int _in_col_up = 0 + col_up;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loop_row:
/* Standardize from: for(row = 1; row < 8191; row++) {...} */
      for (row = 1; row < 8191; row++) {
        int _in_row = row;
        row_down = row + 1;
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_col:
/* Standardize from: for(col = 1; col < 8191; col++) {...} */
        for (col = 1; col < 8191; col++) {
          int _in_col = col;
          col_down = col + 1;
          tmp = 0;
          loop_k_row:
          for (k_row = -1; k_row <= 1; k_row++) {
            int _in_k_row = 0 + k_row;
            loop_k_col:
            for (k_col = -1; k_col <= 1; k_col++) {
              int _in_k_col = 0 + k_col;
              tmp += filter[(((k_row) + 1) * 3) + ((k_col) + 1)] * orig[(_in_row_up + _in_k_row) * 8192 + (_in_col_up + _in_k_col)];
            }
          }
          sol[row * 8192 + col] = tmp;
        }
      }
    }
  }
}