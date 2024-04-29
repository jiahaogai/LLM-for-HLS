#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
/* Standardize from: for(row = 1;row < 8191;row++) {...} */
  for (row = 1; row < 8191; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
/* Standardize from: for(row_up = row - 1;row_up > 0;row_up--) {...} */
    for (row_up = row - 1; row_up > 0; row_up--) {
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_col_up:
      for (col_up = 8190; col_up > 0; col_up--) {
        flit = orig[col_up + row_up * 8192] + filter[0] * flit;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_col:
/* Standardize from: for(col = 1;col < 8191;col++) {...} */
    for (col = 1; col < 8191; col++) {
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_row_up_pad:
      for (row_up = row - 1; row_up > 0; row_up--) {
        flit += orig[col + row_up * 8192] * filter[row_up];
      }
      sol[col + row * 8192] = flit;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_down:
/* Standardize from: for(row_down = row + 1;row_down < 8191;row_down++) {...} */
    for (row_down = row + 1; row_down < 8191; row_down++) {
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_col_down:
      for (col_down = 1; col_down < 8191; col_down++) {
        flit += orig[col_down + row_down * 8192] * filter[row_down];
      }
      sol[col + row * 8192] = flit;
    }
  }
}